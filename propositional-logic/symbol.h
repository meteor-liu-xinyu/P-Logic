#ifndef SYMBOL_H
#define SYMBOL_H

#include <QWidget>
#include <QKeyEvent>

namespace Ui {
class Symbol;
}

class Symbol : public QWidget
{
    Q_OBJECT

public:
    explicit Symbol(QWidget *parent = 0);
    ~Symbol();
    void keyPressEvent(QKeyEvent *k);

signals:
    void sentkey(QString keyname);

private slots:
    void on_not1_clicked();

    void on_and1_clicked();

    void on_or1_clicked();

    void on_not2_clicked();

    void on_and2_clicked();

    void on_or2_clicked();

    void on_leftbracket_clicked();

    void on_rightbracket_clicked();

    void on_sum_clicked();

    void on_prod_clicked();

    void on_key_M_clicked();

    void on_key_m_clicked();

    void on_key_D_clicked();

    void on_equal_clicked();

    void on_comma_clicked();

    void on_condition_clicked();

    void on_doublecondition_clicked();

    void on_nand_clicked();

    void on_nor_clicked();

    void on_key_1_clicked();

    void on_key_0_clicked();

    void on_key_dash_clicked();

    void on_key_A_clicked();

    void on_key_B_clicked();

    void on_key_C_clicked();

    void on_key_D_2_clicked();

    void on_key_X_clicked();

    void on_key_Y_clicked();

    void on_key_Z_clicked();

    void on_key_W_clicked();

    void on_key_xor_clicked();

private:
    Ui::Symbol *ui;
};

#endif // SYMBOL_H
