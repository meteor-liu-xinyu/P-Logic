#ifndef HELPINFOMATION_H
#define HELPINFOMATION_H

#include <QWidget>
#include <QKeyEvent>

namespace Ui {
class HelpInfomation;
}

class HelpInfomation : public QWidget
{
    Q_OBJECT

public:
    explicit HelpInfomation(QWidget *parent = 0);
    ~HelpInfomation();
    void keyPressEvent(QKeyEvent *k);

private:
    Ui::HelpInfomation *ui;
};

#endif // HELPINFOMATION_H
