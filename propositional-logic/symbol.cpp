#include "symbol.h"
#include "ui_symbol.h"

Symbol::Symbol(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Symbol)
{
    ui->setupUi(this);

    // 设置窗口标题
    setWindowTitle("符号");
}

Symbol::~Symbol()
{
    delete ui;
}

void Symbol::keyPressEvent(QKeyEvent *k)
{
    if (k->key() == Qt::Key_Escape)
    {
        this->close();
    }
}

void Symbol::on_not1_clicked()
{
    emit sentkey("not1");
}

void Symbol::on_and1_clicked()
{
    emit sentkey("and1");
}

void Symbol::on_or1_clicked()
{
    emit sentkey("or1");
}

void Symbol::on_not2_clicked()
{
    emit sentkey("not2");
}

void Symbol::on_and2_clicked()
{
    emit sentkey("and2");
}

void Symbol::on_or2_clicked()
{
    emit sentkey("or2");
}

void Symbol::on_leftbracket_clicked()
{
    emit sentkey("leftbracket");
}

void Symbol::on_rightbracket_clicked()
{
    emit sentkey("rightbracket");
}

void Symbol::on_sum_clicked()
{
    emit sentkey("sum");
}

void Symbol::on_prod_clicked()
{
    emit sentkey("prod");
}

void Symbol::on_key_M_clicked()
{
    emit sentkey("key_M");
}

void Symbol::on_key_m_clicked()
{
    emit sentkey("key_m");
}

void Symbol::on_key_D_clicked()
{
    emit sentkey("key_D");
}

void Symbol::on_equal_clicked()
{
    emit sentkey("equal");
}

void Symbol::on_comma_clicked()
{
    emit sentkey("comma");
}

void Symbol::on_condition_clicked()
{
    emit sentkey("condition");
}

void Symbol::on_doublecondition_clicked()
{
    emit sentkey("doublecondition");
}

void Symbol::on_nand_clicked()
{
    emit sentkey("nand");
}

void Symbol::on_nor_clicked()
{
    emit sentkey("nor");
}

void Symbol::on_key_1_clicked()
{
    emit sentkey("key_1");
}

void Symbol::on_key_0_clicked()
{
    emit sentkey("key_0");
}

void Symbol::on_key_dash_clicked()
{
    emit sentkey("key_dash");
}

void Symbol::on_key_A_clicked()
{
    emit sentkey("key_A");
}

void Symbol::on_key_B_clicked()
{
    emit sentkey("key_B");
}

void Symbol::on_key_C_clicked()
{
    emit sentkey("key_C");
}

void Symbol::on_key_D_2_clicked()
{
    emit sentkey("key_D");
}

void Symbol::on_key_X_clicked()
{
    emit sentkey("key_X");
}

void Symbol::on_key_Y_clicked()
{
    emit sentkey("key_Y");
}

void Symbol::on_key_Z_clicked()
{
    emit sentkey("key_Z");
}
void Symbol::on_key_W_clicked()
{
    emit sentkey("key_W");
}

void Symbol::on_key_xor_clicked()
{
    emit sentkey("key_xor");
}
