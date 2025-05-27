#include "keybordshortcut.h"
#include "ui_keybordshortcut.h"

KeybordShortcut::KeybordShortcut(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::KeybordShortcut)
{
    ui->setupUi(this);
}

KeybordShortcut::~KeybordShortcut()
{
    delete ui;
}

void KeybordShortcut::keyPressEvent(QKeyEvent *k)
{
    if (k->key() == Qt::Key_Escape)
    {
        this->close();
    }
}
