#include "calkanuo.h"

Calkanuo::Calkanuo()
{

}

void Calkanuo::Set(const QVector<QChar> &ArgName, const QHash<int,QString> &ToBin, const QVector<int> &Value, const int &mode)
{
    this->Value = Value;
    this->ArgName = ArgName;
    Argnum = ArgName.size();
    this->ToBin = ToBin;
    this->mode = mode;
    if (mode >= 3)
    {
        this->mode = 2;
    }
    PI.clear();
    for (int i = 0; i < pow(2,Argnum); i++)
    {
        if (Value[i] == 1)
        {
            PI.append(i);
        }
    }
}

int Calkanuo::Countone(QString terms) // 计算字符串中1的个数
{
    int count = 0;
    for (const auto& term : terms)
    {
        if (term == '1')
        {
            count++;
        }
    }
    return count;
}

bool Calkanuo::IfNear(const QString& a, const QString& b) // 判断两个字符串是否只有一位不同
{
    int diffCount = 0;
    for (int i = 0; i < a.size(); i++)
    {
        if (a[i] != b[i])
        {
            diffCount++;
        }
        if (diffCount > 1)
        {
            return false;
        }
    }
    return true;
}

QString Calkanuo::Combine(const QString& a, const QString& b) // 合并两个字符串，将不同的位置替换为'-'
{
    QString combined = a;
    for (int i = 0; i < a.size(); i++)
    {
        if (a[i] != b[i])
        {
            combined[i] = '-';
        }
    }
    return combined;
}

int Calkanuo::CountDashes(const QString& str) // 计算字符串中'-'的个数
{
    int count = 0;
    for (int i = 0; i < str.size(); i++)
    {
        if (str[i] == '-')
        {
            count++;
        }
    }
    return count;
}

QString Calkanuo::QM() // 卡诺图化简
{
    QString kanuo;

    bool alltrue = true;
    bool allfalse = true;
    for (const auto& i : Value)
    {
        if (i == 0)
        {
            alltrue = false;
        }
        else // i == 1
        {
            allfalse = false;
        }
        if (allfalse == false && alltrue == false)
        {
            break;
        }
    }
    if (alltrue)
    {
        return "T";
    }
    if (allfalse)
    {
        return "F";
    }

    QVector<QVector<QString>> groups;
    // 初始化groups
    for (int i = 0; i < Argnum+1; i++)
    {
        groups.append(QVector<QString>());
    }

    for (int i = 0; i < PI.size(); i++)
    {
        // 将二进制字符串添加到对应的组中
        QString temp = ToBin[PI[i]];
        groups[Countone(temp)].append(temp);
    }

    endinter = false;
    while (!endinter) // 循环合并项
    {
        groups = QMCombine(groups); // 合并项
    }

    // 生成最终PI
    int finalPIsize = 0;
    QVector<QString> finalPI;
    for (const auto& group : groups)
    {
        for (const auto& term : group)
        {
            finalPI.append(term);
            finalPIsize++;
        }
    }

    // 去除不必要的项
    QVector<QVector<int>> table; // 基本蕴含项表
    QVector<int> row(pow(2,Argnum),0);
    QVector<QString> bin;
    for (int i = 0; i < pow(2,Argnum); i++)
    {
        bin.append(ToBin[i]);
    }
    for (int i = 0; i < finalPIsize; i++)
    {
        table.append(row);
        for (int j = 0; j < pow(2,Argnum); j++)
        {
            bool flag = true;
            for (int k = 0; k < Argnum; k++)
            {
                if (finalPI[i][k] == '1' && bin[j][k] == '0')
                {
                    flag = false;
                    break; // 不满足
                }
                else if (finalPI[i][k] == '0' && bin[j][k] == '1')
                {
                    flag = false;
                    break; // 不满足
                }
            }
            if (flag)
            {
                table[i][j] = 1;
            }
            else
            {
                table[i][j] = 0;
            }
        }
    }

    int tempEPI = 0;
    QHash<int, int> hashTable;
    for ( int i = 0; i < finalPIsize; i++)
    {
        hashTable[i] = -i-1;
    }
    for (int i = 0; i < pow(2,Argnum); i++)
    {
        int count = 0;
        for (int j = 0; j < finalPIsize; j++)
        {
            if (table[j][i] == 1)
            {
                tempEPI = j;
                count ++;
            }
        }
        if (count == 1)
        {
            hashTable[tempEPI] = tempEPI;
        }
    }

    bool flag = false;
    for (int i = 0; i < finalPIsize; i++)
    {
        if (hashTable[i] >= 0)
        {
            flag = true;
        }
    }
    if (!flag)
    {
        hashTable[0] = 0;
    }

    for (int i = 0; i < finalPIsize; i++)
    {
        if (hashTable[i] >= 0) // 是基本蕴含项
        {
            for (int j = table[0].size()-1; j >= 0; j--)
            {
                if (table[i][j] == 1)
                {
                    // 删除该列
                    for (int k = finalPIsize-1; k >= 0; k--)
                    {
                        table[k].remove(j);
                    }
                }
            }
        }
    }

    // 去除不必要的项
    while (1)
    {
        int temprownum = 0;
        int tempcount = 0;
        for (int i = 0; i < finalPIsize; i++)
        {
            int count = 0;
            if (hashTable[i] >= 0)
            {
                continue; // 是基本蕴含项
            }
            // 不是基本蕴含项
            for (int j = 0; j < table[0].size(); j++)
            {
                if (table[i][j] == 1)
                {
                    count ++;
                }
            }

            if (count > tempcount)
            {
                tempcount = count;
                temprownum = i;
            }
        }
        if (tempcount == 0)
        {
            break;
        }
        hashTable[temprownum] = temprownum; // 更改为基本蕴含项
        for (int j = table[0].size()-1; j >= 0; j--)
        {
            if (table[temprownum][j] == 1)
            {
                // 删除该列
                for (int k = finalPIsize-1; k >= 0; k--)
                {
                    table[k].remove(j);
                }
            }
        }
    }

    QVector<QString> finalEPI; // 存储最终的基本蕴含项
    for (int i = 0; i < finalPIsize; i++)
    {
        if (hashTable[i] >= 0)
        {
            finalEPI.append(finalPI[i]);
        }
    }

    // 从finalEPI中计算kanuo化简结果
    for (const auto& term : finalEPI)
    {
        if (mode == 1 && CountDashes(term) < Argnum-1)
        {
            kanuo.append('(');
        }
        for (int i = 0; i < term.size(); i++)
        {
            if (term[i] == '1')
            {
                kanuo.append(ArgName[i]);
            }
            else if (term[i] == '0')
            {
                if (mode == 1)
                {
                    kanuo.append('~');
                    kanuo.append(ArgName[i]);
                }
                else // mode == 2
                {
                    kanuo.append(ArgName[i]);
                    kanuo.append('`');
                }
            }
            if (term[i] != '-' && mode == 1)
            {
                kanuo.append(QChar(0x2227));
            }
        }
        if (mode == 1)
        {
            kanuo.chop(1);
        }
        if (mode == 1)
        {
            if (CountDashes(term) < Argnum-1)
            {
                kanuo.append(')');
            }
            kanuo.append(QChar(0x2228));
        }
        else // mode == 2
        {
            kanuo.append('+');
        }
    }
    kanuo.chop(1);
    return kanuo;
}

QVector<QVector<QString>> Calkanuo::QMCombine(const QVector<QVector<QString>>& groups) // 合并项
{
    endinter = true; // 标记是否已经不能再合并
    QVector<QVector<QString>> nextgroups; // 存储合并后的项
    for (int i = 0; i < Argnum+1; i++)
    {
        nextgroups.append(QVector<QString>());
    }

    QHash<QString, bool> If_in_next; // 标记nextgroups中是否已有
    // 初始化
    for (const auto& group : groups)
    {
        for (const auto& term : group)
        {
            If_in_next[term] = false;
        }
    }

    QVector<QVector<bool>> used; // 标记是否被合并
    for (int i = 0; i < groups.size(); i++)
    {
        used.append(QVector<bool> (groups[i].size(),false));
    }

    for (int i = 0; i < groups.size()-1; i++) // 两两遍历所有组
    {
        for (int j = 0; j < groups[i].size(); j++) // 遍历有i个1的组
        {
            for (int k = 0; k < groups[i+1].size(); k++) // 遍历有i+1个1的组
            {
                if (IfNear(groups[i][j], groups[i+1][k]))
                {
                    int dashesnum = CountDashes(groups[i][j]);
                    if (dashesnum > CountDashes(groups[i+1][k]))
                    {
                        dashesnum = CountDashes(groups[i+1][k]);
                    }
                    QString combined = Combine(groups[i][j], groups[i+1][k]);
                    if (CountDashes(combined) == dashesnum+1)
                    {
                        endinter = false; // 如果有新的合并，则继续合并
                        if (If_in_next[combined] == false) // 如果nextgroups中没有该项
                        {
                            nextgroups[Countone(combined)].append(combined);
                            If_in_next[combined] = true;
                        }
                        // 标记合并的项
                        used[i][j] = true;
                        used[i+1][k] = true;
                    }
                }
            }
        }
    }

    // 将未被合并的项添加到结果中
    for (int i = 0; i < groups.size(); i++)
    {
        for (int j = 0; j < groups[i].size(); j++)
        {
            if (!used[i][j])
            {
                nextgroups[Countone(groups[i][j])].append(groups[i][j]);
            }
        }
    }

    return nextgroups;
}
