#include "modechoose.h"
#include "ui_modechoose.h"

ModeChoose::ModeChoose(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ModeChoose)
{
    ui->setupUi(this);

    buttonGroup.addButton(ui->mode1Button);
    buttonGroup.addButton(ui->mode2Button);
    buttonGroup.addButton(ui->mode3Button);
    buttonGroup.addButton(ui->mode4Button);
    buttonGroup.addButton(ui->mode5Button);
    buttonGroup.addButton(ui->mode6Button);

}

ModeChoose::~ModeChoose()
{
    delete ui;

    mode = 2;
}

void ModeChoose::keyPressEvent(QKeyEvent *k)
{
    if (k->key() == Qt::Key_Return || k->key() == Qt::Key_Enter)
    {
        qDebug() << "enter pressed";
        on_commitButton_clicked();
    }
    else if (k->key() == Qt::Key_Up)
    {
        QRadioButton *checkedButton = static_cast<QRadioButton*>(buttonGroup.checkedButton());
        QList<QAbstractButton*> buttons = buttonGroup.buttons();
        int currentIndex = buttons.indexOf(checkedButton);
        if (currentIndex > 0)
        {
            buttons[currentIndex - 1]->setChecked(true);
        }
        else
        {
            buttons[5]->setChecked(true);
        }
    }
    else if (k->key() == Qt::Key_Down)
    {
        QRadioButton *checkedButton = static_cast<QRadioButton*>(buttonGroup.checkedButton());
        QList<QAbstractButton*> buttons = buttonGroup.buttons();
        int currentIndex = buttons.indexOf(checkedButton);
        if (currentIndex < 5)
        {
            buttons[currentIndex + 1]->setChecked(true);
        }
        else
        {
            buttons[0]->setChecked(true);
        }
    }
    else if (k->key() == Qt::Key_1)
    {
        ui->mode1Button->setChecked(true);
    }
    else if (k->key() == Qt::Key_2)
    {
        ui->mode2Button->setChecked(true);
    }
    else if (k->key() == Qt::Key_3)
    {
        ui->mode3Button->setChecked(true);
    }
    else if (k->key() == Qt::Key_4)
    {
        ui->mode4Button->setChecked(true);
    }
    else if (k->key() == Qt::Key_5)
    {
        ui->mode5Button->setChecked(true);
    }
    else if (k->key() == Qt::Key_6)
    {
        ui->mode6Button->setChecked(true);
    }
    else if (k->key() == Qt::Key_Escape)
    {
        this->close();
    }
}

void ModeChoose::on_commitButton_clicked()
{
    if (ui->mode1Button->isChecked())
    {
        mode = 1;
    }
    else if (ui->mode2Button->isChecked())
    {
        mode = 2;
    }
    else if (ui->mode3Button->isChecked())
    {
        mode = 3;
    }
    else if (ui->mode4Button->isChecked())
    {
        mode = 4;
    }
    else if (ui->mode5Button->isChecked())
    {
        mode = 5;
    }
    else if (ui->mode6Button->isChecked())
    {
        mode = 6;
    }

//    qDebug() << "Selected mode = " << mode;

    emit modeSelected(mode);

    this->hide();
}

