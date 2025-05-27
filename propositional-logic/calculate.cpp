#include "calculate.h"

Calculate::Calculate()
{
}

void Calculate::Set(const QString &input, const QVector<QChar> &ArgName, const QHash<int,QString> &ToBin, const int &mode,
                    const QVector<int> &unrelatedItems, const QHash<int, bool> &If_unrelated)
{
    this->input = input;
    this->ArgName = ArgName;
    Argnum = ArgName.size();
    this->ToBin = ToBin;
    this->mode = mode;
    this->unrelatedItems = unrelatedItems;
    this->If_unrelated = If_unrelated;
}

int Calculate::CalculateValue(int n) // 计算真值表n行的真值
{
    QString binstr = ToBin[n]; // 获取二进制数
    Operation operation;

    // 用T/F替换ArgName对应的值,存入temp中
    QString temp = input;
    for (int i = 0; i < input.length(); i++)
    {
        for (int j = 0; j < Argnum; j++)
        {
            if (temp[i] == ArgName[j])
            {
                if (binstr[j] == '1')
                {
                    temp[i] = 'T';
                }
                else
                {
                    temp[i] = 'F';
                }
            }
        }
    }

    while (temp[0] == '(')
    {
        // 计算最靠左侧的最内侧的一对括号边界
        int right = operation.FindRight(temp);
        int left = operation.FindLeft(temp);
        // 计算Not运算
        if (mode == 1)
        {
            for (int i = left+1; i < right; i++)
            {
                if (temp[i] == '~')
                {
                    temp[i+1] = operation.Not(temp[i+1]);
                    temp.remove(i, 1);
                    right--;
                }
            }
        }
        else if (mode == 2)
        {
            for (int i = left+1; i < right; i++)
            {
                if (temp[i] == '`')
                {
                    temp[i-1] = operation.Not(temp[i-1]);
                    temp.remove(i, 1);
                    right--;
                }
            }
            // 补上省略的*
            for (int i = left+1; i < right-1; i++)
            {
                if ((temp[i] >= 'A' && temp[i] <= 'Z') && ((temp[i+1] >= 'A' && temp[i+1] <='Z')))
                {
                    temp.insert(i+2,")");
                    temp.insert(i+1, QChar(0xD7));
                    temp.insert(i, "(");
                    right = operation.FindRight(temp);
                    left = operation.FindLeft(temp);
                    break;
                }
            }
        }

        // 计算其他运算
        for (int i = left+2; i < right-1; i++)
        {
            if (temp[i] == QChar(0x2227) || temp[i] == QChar(0xD7))// 合取符号、乘号符号
            {
                temp[i+1] = operation.And(temp[i-1], temp[i+1]);
            }
            else if (temp[i] == QChar(0x2228) || temp[i] == '+')// 析取符号、加号符号
            {
                temp[i+1] = operation.Or(temp[i-1], temp[i+1]);
            }
            else if (temp[i] == QChar(0x2192))// 条件符号
            {
                temp[i+1] = operation.If(temp[i-1], temp[i+1]);
            }
            else if (temp[i] == QChar(0x2194))// 双条件符号
            {
                temp[i+1] = operation.Iff(temp[i-1], temp[i+1]);
            }
            else if (temp[i] == QChar(0x2295))// 异或符号
            {
                temp[i+1] = operation.Xor(temp[i-1], temp[i+1]);
            }
            else if (temp[i] == QChar(0x2191))// 与非符号
            {
                temp[i+1] = operation.Nand(temp[i-1], temp[i+1]);
            }
            else if (temp[i] == QChar(0x2193))//// 或非符号
            {
                temp[i+1] = operation.Nor(temp[i-1], temp[i+1]);
            }
            temp.remove(i-1, 2);
            right -= 2;
            i--;
        }

        // 删除剩下的空括号
        temp.remove(left+2, 1);
        temp.remove(left, 1);
    }

    if (temp[0] == 'T')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

QVector<int> Calculate::Cal() // 计算真值表
{
    QVector<int> Value;

    int powArgnum = pow(2,Argnum);
    if (mode == 3 || mode == 4 || mode == 5)
    {
        if (input[0] == 'M' && input[1] == '(' && mode == 3)
        {
            for (int i = 0; i < powArgnum; i++)
            {
                Value.append(1);
            }
        }
        else if (input[0] == 'm' && input[1] == '(' && (mode == 4 || mode == 5))
        {
            for (int i = 0; i < powArgnum; i++)
            {
                Value.append(0);
            }
        }
        else
        {
            QMessageBox::warning(this,"错误","输入有误");
//            emit calerrorInput(15);
            Value.clear();
            return Value;
        }

        // 读取()中的逗号分隔的数字，更改对应Value的值
        QString temp;
        int i = 2;
        for (; input[i] != ')'; i++)
        {
            if (!(input[i] >= '0' && input[i] <= '9') && input[i]!= ',')
            {
                QMessageBox::warning(this,"错误","输入有误");
//                emit calerrorInput(16);
                Value.clear();
                return Value;
            }
            if (input[i] != ',')
            {
                temp.append(input[i]);
            }
            else
            {
                int tempnum = temp.toInt();
                Value[tempnum] = !Value[tempnum];
                temp.clear();
            }
        }
        int tempnum = temp.toInt();
        Value[tempnum] = !Value[tempnum];
        temp.clear();

        if (mode == 5)
        {
            input.remove(0, i+1);
            i = 0;
            if (input[i] == '+' && input[i+1] == QChar(0x2211) && input[i+2] == 'D')
            {
                input.remove(i, 3);
                i++;
                for (; input[i] != ')'; i++)
                {
                    if (!(input[i] >= '0' && input[i] <= '9') && input[i]!= ',')
                    {
                        QMessageBox::warning(this,"错误","输入有误");
            //            emit calerrorInput(17);
                        Value.clear();
                        return Value;
                    }
                    if (input[i] != ',')
                    {
                        temp.append(input[i]);
                    }
                    else
                    {
                        int tempnum = temp.toInt();
                        unrelatedItems.append(tempnum);
                        If_unrelated[tempnum] = true;
                        temp.clear();
                    }
                }
                int tempnum = temp.toInt();
                unrelatedItems.append(tempnum);
                If_unrelated[tempnum] = true;

                int unrelatedItemsSize = unrelatedItems.size();

                QHash<int,QString> tempToBin; // 临时哈希表
                for (int j = 0; j < pow(2,unrelatedItemsSize); j++)
                {
                    QString binstr;
                    for (int k = 0; k < unrelatedItemsSize; k++)
                    {
                        binstr += (j >> k) & 1 ? '1' : '0'; // 将十进制数转换为二进制数
                    }
                    // 反转字符串
                    for (int k = 0; k < binstr.length() / 2; k++)
                    {
                        QChar temp = binstr[k];
                        binstr[k] = binstr[binstr.length() - k - 1];
                        binstr[binstr.length() - k - 1] = temp;
                    }
                    tempToBin[j] = binstr;
                }

                QVector<QString> kanuo_all;
                for (int j = 0; j < pow(2,unrelatedItemsSize); j++)
                {
                    for (int k = 0; k < unrelatedItemsSize; k++)
                    {
                        Value[unrelatedItems[k]] = tempToBin[j][k].digitValue();
                    }
                    calkanuo = new Calkanuo;
                    calkanuo->Set(ArgName,ToBin,Value,mode);
                    kanuo_all.append(calkanuo->QM());
                }

                int j = 0;
                for (int k = 0; k < pow(2,unrelatedItemsSize); k++)
                {
                    if (kanuo_all[j].size()>kanuo_all[k].size())
                    {
                        j = k;
                    }
                }

                for (int k = 0; k < unrelatedItemsSize; k++)
                {
                    Value[unrelatedItems[k]] = tempToBin[j][k].digitValue();
                }
            }
        }
    }
    else
    {
        for (int i = 0; i < powArgnum; i++)
        {
            Value.append(CalculateValue(i));
        }
    }

    return Value;
}

QHash<int, bool> Calculate::getUnrelated()
{
    return If_unrelated;
}

Calculate::~Calculate()
{

}
