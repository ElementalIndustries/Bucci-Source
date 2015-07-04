#include "buccimain.h"
#include "ui_buccimain.h"

BucciMain::BucciMain(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BucciMain)
{
    ui->setupUi(this);

    bucciGame = NULL;
}

BucciMain::~BucciMain()
{
    delete ui;
}

void BucciMain::on_pushButton_4_clicked()
{
    this->close();
}

void BucciMain::on_pushButton_clicked()
{
    if(bucciGame == NULL)
    {
        bucciGame = new BucciGame();
    }

    bucciGame->show();
}
