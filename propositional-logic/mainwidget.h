#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QString>
#include <QHash>
#include <QVector>
#include <QDebug>
#include <cmath>
#include <QMessageBox>
#include <QLineEdit>
#include <QKeyEvent>

#include "modechoose.h"
#include "calculate.h"
#include "calkanuo.h"
#include "paradigms.h"
#include "maketruthtable.h"
#include "kmap.h"
#include "tableinput.h"
#include "symbol.h"
#include "helpinfomation.h"
#include "keybordshortcut.h"

namespace Ui {
class MainWidget;
}

class Calculate;
class Paradigms;
class Calkanuo;
class Kmap;
class TableInput;
class Symbol;
class HelpInfomation;
class KeybordShortcut;

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0);
    void InitMode();
    void keyPressEvent(QKeyEvent *k);

    ~MainWidget();

signals:
    void errorInput(int errorcode);

private slots:
    void on_inputSettingButton_clicked();

    void receiveModeSelected(int mode);

    void on_symbolButton_clicked();

    void on_helpButton_clicked();

    void on_commitButton_clicked();

    void on_clearButton_clicked();

    void on_delButton_clicked();

    void on_truthtableButton_clicked();

    void on_kmapButton_clicked();

    void on_simplifyButton_clicked();

    void on_cnfButton_clicked();

    void on_dnfButton_clicked();

    void receiveErrorInput(int errorcode);

    void receivecalErrorInput(int errorcode);

    void resetLineEdit();

    void getTableinput(QString trans_input);

    void receiveKey(QString keyname);

    void on_shortcartButton_clicked();

private:
    Ui::MainWidget *ui;

    ModeChoose *modechooseWidget = NULL;
    MakeTruthTable *maketruthtable = NULL;
    Calculate *calculate = NULL;
    Paradigms *paradigms = NULL;
    Calkanuo *calkanuo = NULL;
    Kmap *kmap = NULL;
    TableInput *tableinput = NULL;
    Symbol *symbol = NULL;
    HelpInfomation *helpinfomation = NULL;
    KeybordShortcut *keybordshortcut = NULL;

    QString input;
    int mode; // 1: 离散数学符号体系 2: 数字逻辑符号体系 3: 连乘 4: 连加 5: 真值表输入
    QString initialinput; // 初始输入
    QVector<QChar> ArgName; // 命题变元名
    int Argnum; // 命题变元个数
    QVector<int> Value; // 真值
    QVector<int> PI;
    QVector<QString> NF;
    QString kanuo; // 卡诺图化简结果
    QVector<int> unrelatedItems; // 无关项
    QHash<int, bool> If_unrelated; // 是否无关项

    QHash<QString, int> ToDec; // 哈希表
    QHash<int, QString> ToBin; // 哈希表

    void InitAll();
    bool TransLegal();
    void inputProcess();
    void FindArg();
    void BuildHashTable(); // 建立哈希表

};

#endif // MAINWIDGET_H
