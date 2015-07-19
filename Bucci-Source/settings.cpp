#include "settings.h"
#include "ui_settings.h"
#include <fstream>

using namespace std;

Settings::Settings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);

    rename("../Bucci-Source/Data/settings.bdf", "../Bucci-Source/Data/settings.txt");

    ifstream settings;

    settings.open("../Bucci-Source/Data/settings.txt");

    int oppCount;
    bool mode;

    if(settings.is_open())
    {
        settings >> oppCount;
        ui->opponentCounter->setValue(oppCount);
        settings >> mode;
        ui->easy->setChecked(mode);
        settings >> mode;
        ui->medium->setChecked(mode);
        settings >> mode;
        ui->hard->setChecked(mode);
    }

    settings.close();

    rename("../Bucci-Source/Data/settings.txt", "../Bucci-Source/Data/settings.bdf");

    connect(ui->opponentCounter, SIGNAL(valueChanged(int)), this, SLOT(enableSave()));
    connect(ui->easy, SIGNAL(toggled(bool)), this, SLOT(enableSave()));
    connect(ui->medium, SIGNAL(toggled(bool)), this, SLOT(enableSave()));
    connect(ui->hard, SIGNAL(toggled(bool)), this, SLOT(enableSave()));

    ui->save->setEnabled(false);
}

Settings::~Settings()
{
    delete ui;
}

void Settings::on_ok_clicked()
{
    this->close();
}

void Settings::on_reset_clicked()
{
    ui->opponentCounter->setValue(1);
    ui->easy->setChecked(true);
    ui->medium->setChecked(false);
    ui->hard->setChecked(false);
}

void Settings::on_save_clicked()
{
    rename("../Bucci-Source/Data/settings.bdf", "../Bucci-Source/Data/settings.txt");

    ofstream save;

    save.open("../Bucci-Source/Data/settings.txt");

    save << ui->opponentCounter->value() << endl;
    save << ui->easy->isChecked() << endl;
    save << ui->medium->isChecked() << endl;
    save << ui->hard->isChecked() << endl;

    save.close();

    rename("../Bucci-Source/Data/settings.txt", "../Bucci-Source/Data/settings.bdf");
}

void Settings::enableSave()
{
    ui->save->setEnabled(true);
}
