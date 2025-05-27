#include "operation.h"

Operation::Operation()
{

}

Operation::~Operation()
{

}

int Operation::FindRight(const QString& temp) // 找到0开始第一个右括号的位置
{
    int i = 0;
    while (temp[i] != ')')
    {
        i++;
    }
    return i;
}

int Operation::FindLeft(const QString& temp) // 找到0开始第一个右括号对应的左括号的位置
{
    int i = FindRight(temp); // 找到0开始第一个右括号的位置
    while (temp[i] != '(')
    {
        i--;
    }
    return i;
}

QChar Operation::Not(QChar A)
{
    return A == QLatin1Char('T') ? QLatin1Char('F') : QLatin1Char('T');
}

QChar Operation::And(QChar A, QChar B)
{
    return (A == QLatin1Char('T') && B == QLatin1Char('T')) ? QLatin1Char('T') : QLatin1Char('F');
}

QChar Operation::Or(QChar A, QChar B)
{
    return (A == QLatin1Char('T') || B == QLatin1Char('T')) ? QLatin1Char('T') : QLatin1Char('F');
}

QChar Operation::If(QChar A, QChar B)
{
    return (A == QLatin1Char('T') && B == QLatin1Char('F')) ? QLatin1Char('F') : QLatin1Char('T');
}

QChar Operation::Iff(QChar A, QChar B) // 双条件
{
    return (A == B) ? QLatin1Char('T') : QLatin1Char('F');
}

QChar Operation::Xor(QChar A, QChar B) // 异或
{
    return (A != B) ? QLatin1Char('T') : QLatin1Char('F');
}

QChar Operation::Nand(QChar A, QChar B) // 与非
{
    return Not(And(A, B));
}

QChar Operation::Nor(QChar A, QChar B) // 或非
{
    return Not(Or(A, B));
}
