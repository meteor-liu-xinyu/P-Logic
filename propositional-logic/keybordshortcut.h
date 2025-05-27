#ifndef KEYBORDSHORTCUT_H
#define KEYBORDSHORTCUT_H

#include <QWidget>
#include <QKeyEvent>

namespace Ui {
class KeybordShortcut;
}

class KeybordShortcut : public QWidget
{
    Q_OBJECT

public:
    explicit KeybordShortcut(QWidget *parent = 0);
    ~KeybordShortcut();

    void keyPressEvent(QKeyEvent *k);

private:
    Ui::KeybordShortcut *ui;
};

#endif // KEYBORDSHORTCUT_H
