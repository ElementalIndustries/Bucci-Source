#ifndef BUCCIMAIN_H
#define BUCCIMAIN_H

#include <QMainWindow>
#include "buccigame.h"
#include "settings.h"
#include "stats.h"

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
    void on_exit_clicked();

    void on_settings_clicked();

    void on_stats_clicked();

    void on_newGame_clicked();

    void on_howToPlay_clicked();

    void on_resumeGame_clicked();

private:
    Ui::BucciMain *ui;
    BucciGame *bucciGame;
    Settings *settings;
    Stats *stats;
};

#endif // BUCCIMAIN_H
