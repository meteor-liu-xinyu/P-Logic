#ifndef KMAP_H
#define KMAP_H

#include <QWidget>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QStringList>
#include <QVector>
#include <QHeaderView>
#include <QKeyEvent>

class Kmap : public QWidget
{
    Q_OBJECT

public:
    explicit Kmap(QWidget *parent = 0);
    void generateKmap(const QVector<QChar> &ArgName, const QVector<int> &Value, const QHash<int,bool> &If_unrelated);
    QVector<QString> GenerateGrayCode(int n);

    void keyPressEvent(QKeyEvent *k);

    ~Kmap();

private:

    QTableWidget* tableWidget; // 表格控件
    QVBoxLayout* mainLayout;   // 主布局
};

#endif // KMAP_H
