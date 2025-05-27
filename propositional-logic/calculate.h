#ifndef CALCULATE_H
#define CALCULATE_H

#include <QString>
#include <QWidget>
#include <QHash>
#include <QVector>
#include <QDebug>
#include <cmath>
#include <QMessageBox>

#include "operation.h"
#include "calkanuo.h"

class Operation;
class Calkanuo;

namespace Ui {
class Calculate;
}

class Calculate : public QWidget
{
//    Q_OBJECT

public:
    Calculate();
    void Set(const QString &input, const QVector<QChar> &ArgName, const QHash<int,QString> &ToBin, const int &mode,
             const QVector<int> &unrelatedItems, const QHash<int, bool> &If_unrelated);
    QVector<int> Cal(); // 计算真值表
    QHash<int, bool> getUnrelated();
    ~Calculate();

signals:
//    void calerrorInput(int errorcode);

private slots:

private:
    Calkanuo *calkanuo = NULL;

    QString input;
    QVector<QChar> ArgName;
    QHash<int,QString> ToBin;
    int Argnum;
    int mode;
    QVector<int> unrelatedItems;
    QHash<int, bool> If_unrelated;

    int CalculateValue(int n); // 计算真值表n行的真值
};



#endif // CALCULATE_H
