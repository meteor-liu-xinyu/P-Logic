#ifndef OPERATION_H
#define OPERATION_H

#include <QWidget>
#include <QVector>
#include <QDebug>

using namespace std;

class Operation
{

public:
    Operation();
    ~Operation();

    int FindLeft(const QString& temp);
    int FindRight(const QString& temp);

    QChar Not(QChar A);
    QChar And(QChar A, QChar B);
    QChar Or(QChar A, QChar B);
    QChar If(QChar A, QChar B);
    QChar Iff(QChar A, QChar B);
    QChar Xor(QChar A, QChar B);
    QChar Nand(QChar A, QChar B);
    QChar Nor(QChar A, QChar B);

};





#endif // OPERATION_H
