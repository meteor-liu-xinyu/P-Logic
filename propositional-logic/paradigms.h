#ifndef PARADIGMS_H
#define PARADIGMS_H

#include <QString>
#include <QHash>
#include <QVector>
#include <QDebug>
#include <cmath>
#include <QMessageBox>

class Paradigms
{
//    Q_OBJECT
public:
    Paradigms();
    ~Paradigms();
    void Set(const QVector<QChar> &ArgName, const QHash<int,QString> &ToBin, const QVector<int> &Value, const int &mode);
    QVector<QString> NF();

private:
    QVector<int> Value;
    QVector<QChar> ArgName;
    QHash<int,QString> ToBin;
    int mode;
    int Argnum;
};

#endif // PARADIGMS_H
