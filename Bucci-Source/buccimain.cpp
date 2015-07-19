#include "buccimain.h"
#include "ui_buccimain.h"
#include <QDebug>
#include "settings.h"

BucciMain::BucciMain(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BucciMain)
{
    ui->setupUi(this);

    QWidget::setFixedSize(this->width(), this->height());

    QPixmap bkgnd("../Bucci-Source/Images/ElementalIdenticon.png");

    QPalette palette;
    palette.setBrush(QPalette::Background , bkgnd);
    this->setPalette(palette);

    bucciGame = NULL;
    settings = NULL;
    stats = NULL;
}//end of BucciMain c'tor

BucciMain::~BucciMain()
{
    qDebug() << "Main dec'tor called";
    delete ui;
    delete bucciGame;
    delete settings;
    delete stats;
}//end of BucciMain dec'tor

void BucciMain::on_newGame_clicked()
{
    if(bucciGame == NULL)
    {
        bucciGame = new BucciGame(false);
    }
    else
    {
        delete bucciGame;
        bucciGame = new BucciGame(false);
    }

    bucciGame->show();

}//end of on_newGame_clicked

void BucciMain::on_exit_clicked()
{
    this->close();
}//end of on_exit_clicked

void BucciMain::on_settings_clicked()
{
    if(settings != NULL)
    {
        delete settings;
    }

    settings = new Settings();
    settings->show();
}//end of on_settings_clicked

void BucciMain::on_stats_clicked()
{
    if(stats != NULL)
    {
        delete stats;
    }

    stats = new Stats();
    stats->show();

}//end of on_stats_clicked()

void BucciMain::on_howToPlay_clicked()
{

}//end of on_howToPlay_clicked()

void BucciMain::on_resumeGame_clicked()
{
    if(bucciGame != NULL)
    {
        delete bucciGame;
    }

    bucciGame = new BucciGame(true);

    bucciGame->show();
}
