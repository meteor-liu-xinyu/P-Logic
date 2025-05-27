#ifndef MAKETRUTHTABLE_H
#define MAKETRUTHTABLE_H

#include <QWidget>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QStringList>
#include <QVector>
#include <QHeaderView>
#include <QKeyEvent>

class MakeTruthTable : public QWidget
{
    Q_OBJECT

public:
    explicit MakeTruthTable(QWidget *parent = nullptr);
    ~MakeTruthTable();

    void keyPressEvent(QKeyEvent *k);

    // 用于生成真值表的函数
    void generateTruthTable(const QVector<QChar> &ArgName, const QString& initialinput,
                            const QHash<int, QString>& ToBin, const QVector<int>& Value,
                            const QHash<int,bool>& If_unrelated);

private:

    QTableWidget* tableWidget; // 表格控件
    QVBoxLayout* mainLayout;   // 主布局
};

#endif // MAKETRUTHTABLE_H
