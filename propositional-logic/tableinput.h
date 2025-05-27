#ifndef TABLEINPUT_H
#define TABLEINPUT_H

#include <QWidget>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QString>
#include <QHash>
#include <QVector>
#include <QDebug>
#include <QMessageBox>
#include <QLineEdit>
#include <QKeyEvent>
#include <QStringList>
#include <cmath>
#include <QKeyEvent>

#include <symbol.h>
#include <mainwidget.h>

namespace Ui {
class TableInput;
}

class Symbol;
class MainWidget;

class TableInput : public QWidget
{
    Q_OBJECT

public:
    explicit TableInput(QWidget *parent = 0);
    ~TableInput();
    void keyPressEvent(QKeyEvent *k);
signals:
    void sentinput(QString trans_input);
    void enterPressed();

private slots:
    void on_commitButton_clicked();
    void tableinputStart();
    void onCellChanged(int row, int column);

    void on_finishButton_clicked();

    void receiveKey(QString keyname);

    void onCurrentItemChanged(QTableWidgetItem* currentItem, QTableWidgetItem* previousItem);

    void on_symbolButton_clicked();

    void nextItem();


private:
    Ui::TableInput *ui;
    Symbol *symbol = NULL;

    QVector<QChar> ArgName; // 命题变元名
    int Argnum; // 命题变元个数
    QVector<int> Value; // 真值
    QHash<int,QString> ToBin;
    QString trans_input;
    QHash<int, bool> If_unrelated; // 是否无关项
    QVector<int> unrelatedItems; // 无关项

    int now_row;
    int now_column;

};

#endif // TABLEINPUT_H
