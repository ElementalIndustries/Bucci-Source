#ifndef BUCCIMAIN_H
#define BUCCIMAIN_H

#include <QMainWindow>
#include "buccigame.h"

namespace Ui {
class BucciMain;
}

class BucciMain : public QMainWindow
{
    Q_OBJECT

public:
    explicit BucciMain(QWidget *parent = 0);
    ~BucciMain();

private slots:
    void on_pushButton_4_clicked();

    void on_pushButton_clicked();

private:
    Ui::BucciMain *ui;
    BucciGame *bucciGame;
};

#endif // BUCCIMAIN_H
