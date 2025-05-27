#include "paradigms.h"

Paradigms::Paradigms()
{

}

Paradigms::~Paradigms()
{

}

void Paradigms::Set(const QVector<QChar> &ArgName, const QHash<int,QString> &ToBin, const QVector<int> &Value, const int &mode)
{
    this->Value = Value;
    this->ArgName = ArgName;
    Argnum = ArgName.size();
    this->ToBin = ToBin;
    this->mode = mode;
}

QVector<QString> Paradigms::NF()
{
    if (mode == 4 || mode == 3 || mode == 5)
    {
        mode = 2; // 化归为2
    }
    QVector<QString> NF;

    bool alltrue = true; // 判断是否为永真式
    bool allfalse = true; // 判断是否为重言式
    for (const auto& i : Value)
    {
        if (i == 0)
        {
            alltrue = false;
        }
        else
        {
            allfalse = false;
        }
        if (!alltrue && !allfalse) // 既不是永真式也不是重言式
        {
            break;
        }
    }

    QString NFstr[2] = {};
    QString NFMstr[2] = {"∏ M(","∑ m("};

    int powArgnum = pow(2,Argnum);
    int count[2] = {0, 0};
    for (int i = 0; i < powArgnum; i++)
    {
        int CorD = Value[i]; // 0--CNF, 1--DNF
        NFMstr[CorD].append(QString::number(i));
        NFMstr[CorD].append(',');
        QString binstr = ToBin[i]; // 获取二进制数
        if (!(CorD == 1 && mode == 2))
        {
            NFstr[Value[i]].append('(');
        }
        for (int j = 0; j < Argnum; j++)
        {
            if (binstr[j] == '1' - CorD)
            {
                if (mode == 1)
                {
                    NFstr[CorD].append('~');
                    NFstr[CorD].append(ArgName[j]);
                }
                else if (mode == 2)
                {
                    NFstr[CorD].append(ArgName[j]);
                    NFstr[CorD].append('`');
                }
            }
            else
            {
                NFstr[CorD].append(ArgName[j]);
            }
            if (j != Argnum-1)
            {
                if (CorD == 0)
                {
                    if (mode == 1)
                    {
                        NFstr[0].append(QChar(0x2228));
                    }
                    else if (mode == 2)
                    {
                        NFstr[0].append('+');
                    }
                }
                else // CorD == 1
                {
                    if (mode == 1)
                    {
                        NFstr[1].append(QChar(0x2227));
                    }
                }
            }
        }
        if (CorD == 0)
        {
            NFstr[0].append(')');
            if (mode == 1)
            {
                NFstr[0].append(QChar(0x2227));
            }
        }
        else // CorD == 1
        {
            if (mode == 1)
            {
                NFstr[1].append(')');
                NFstr[1].append(QChar(0x2228));
            }
            else if (mode == 2)
            {
                NFstr[1].append('+');
            }
        }
        count[CorD]++;
        if (count[CorD] % 4 == 0 && NFstr[CorD][NFstr[CorD].length()-1] != '\n' && count[CorD] != 0)
        {
            NFstr[CorD].append('\n');
        }
    }

    if (!alltrue)
    {
        if (NFstr[0][NFstr[0].length()-1] == '\n')
        {
            NFstr[0].chop(1);
        }
    }
    if (!allfalse)
    {
        if (NFstr[1][NFstr[1].length()-1] == '\n')
        {
            NFstr[1].chop(1);
        }
    }
    if (mode == 1 && !alltrue)
    {
        NFstr[0].chop(1);
    }
    if (alltrue)
    {
        NFstr[0] = 'T';
        NFMstr[0] = 'T';
    }
    else
    {
        NFMstr[0].chop(1);
        NFMstr[0].append(')');
    }
    if (allfalse)
    {
        NFstr[1] = 'F';
        NFMstr[1] = 'F';
    }
    else
    {
        NFstr[1].chop(1);
        NFMstr[1].chop(1);
        NFMstr[1].append(')');
    }

    NF.append(NFstr[0]);
    NF.append(NFstr[1]);
    NF.append(NFMstr[0]);
    NF.append(NFMstr[1]);
    return NF;
}
