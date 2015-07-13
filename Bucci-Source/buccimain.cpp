#include "buccimain.h"
#include "ui_buccimain.h"
#include <QDebug>
#include "settings.h"

BucciMain::BucciMain(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BucciMain)
{
    ui->setupUi(this);

    bucciGame = NULL;
    settings = NULL;
}//end of BucciMain c'tor

BucciMain::~BucciMain()
{
    qDebug() << "Main dec'tor called";
    delete ui;
    delete bucciGame;
    delete settings;
}//end of BucciMain dec'tor

void BucciMain::on_newGame_clicked()
{
    if(bucciGame == NULL)
    {
        bucciGame = new BucciGame();
    }
    else
    {
        delete bucciGame;
        bucciGame = new BucciGame();
    }

    bucciGame->show();

}//end of on_newGame_clicked

void BucciMain::on_exit_clicked()
{
    this->close();
}//end of on_exit_clicked

void BucciMain::on_settings_clicked()
{
    if(settings == NULL)
    {
        settings = new Settings();
    }

    settings->show();
}//end of on_settings_clicked

void BucciMain::on_stats_clicked()
{

}//end of on_stats_clicked()

void BucciMain::on_howToPlay_clicked()
{

}//end of on_howToPlay_clicked()
