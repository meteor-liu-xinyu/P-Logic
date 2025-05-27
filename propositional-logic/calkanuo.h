#ifndef CALKANUO_H
#define CALKANUO_H

#include <QString>
#include <QHash>
#include <QVector>
#include <QDebug>
#include <cmath>
#include <QMessageBox>

class Operation;

class Calkanuo
{
//    Q_OBJECT

public:
    Calkanuo();
    void Set(const QVector<QChar> &ArgName, const QHash<int,QString> &ToBin, const QVector<int> &Value, const int &mode);
    QString QM();

signals:

private:
    QVector<int> PI;
    bool endinter; // 是否结束QM合并循环
    QVector<int> Value;
    QVector<QChar> ArgName;
    QHash<int,QString> ToBin;
    int mode;
    int Argnum;

    int Countone(QString terms);
    bool IfNear(const QString& a, const QString& b);
    QString Combine(const QString& a, const QString& b);
    int CountDashes(const QString& str);
    QVector<QVector<QString>> QMCombine(const QVector<QVector<QString>>& groups);
};

#endif // CALKANUO_H
