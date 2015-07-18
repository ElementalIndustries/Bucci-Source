#include "stats.h"
#include "ui_stats.h"
#include <fstream>

using namespace std;

Stats::Stats(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Stats)
{
    ui->setupUi(this);

    rename("../Bucci-Source/Data/stats.bdf", "../Bucci-Source/Data/stats.txt");

    ifstream stats;

    stats.open("../Bucci-Source/Data/stats.txt");

    int playerData;

    if(stats.is_open())
    {
        stats >> playerData;
        ui->winsCount->setText(QString::number(playerData));
        stats >> playerData;
        ui->losesCount->setText(QString::number(playerData));
        stats >> playerData;
        ui->cardsInHandCount->setText(QString::number(playerData));
    }

    stats.close();

    rename("../Bucci-Source/Data/stats.txt", "../Bucci-Source/Data/stats.bdf");
}

Stats::~Stats()
{
    delete ui;
}

void Stats::on_ok_clicked()
{
    this->close();
}

void Stats::on_reset_clicked()
{
    rename("../Bucci-Source/Data/stats.bdf", "../Bucci-Source/Data/stats.txt");

    ofstream reset;
    reset.open("../Bucci-Source/Data/stats.txt");
    for(int i = 0; i < 3; i++)
    {
        reset << 0 << endl;
    }

    reset.close();

    ifstream stats;
    int playerData;

    stats.open("../Bucci-Source/Data/stats.txt");

    if(stats.is_open())
    {
        stats >> playerData;
        ui->winsCount->setText(QString::number(playerData));
        stats >> playerData;
        ui->losesCount->setText(QString::number(playerData));
        stats >> playerData;
        ui->cardsInHandCount->setText(QString::number(playerData));
    }

    stats.close();

    rename("../Bucci-Source/Data/stats.txt", "../Bucci-Source/Data/stats.bdf");
}
