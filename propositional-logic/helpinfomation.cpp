#include "helpinfomation.h"
#include "ui_helpinfomation.h"

HelpInfomation::HelpInfomation(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HelpInfomation)
{
    ui->setupUi(this);
}

HelpInfomation::~HelpInfomation()
{
    delete ui;
}

void HelpInfomation::keyPressEvent(QKeyEvent *k)
{
    if (k->key() == Qt::Key_Escape)
    {
        this->close();
    }
}
