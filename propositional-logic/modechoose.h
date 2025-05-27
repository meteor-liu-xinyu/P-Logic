#ifndef MODECHOOSE_H
#define MODECHOOSE_H

#include <QWidget>
#include <QPushButton>
#include <QDebug>
#include <QKeyEvent>
#include <QButtonGroup>
#include <QList>

namespace Ui {
class ModeChoose;
}

class ModeChoose : public QWidget
{
    Q_OBJECT

public:
    explicit ModeChoose(QWidget *parent = 0);
    void keyPressEvent(QKeyEvent *k);
    ~ModeChoose();

signals:
    void modeSelected(int mode);

private slots:
    void on_commitButton_clicked();

private:
    Ui::ModeChoose *ui;
    int mode;
    QButtonGroup buttonGroup;
};

#endif // MODECHOOSE_H
