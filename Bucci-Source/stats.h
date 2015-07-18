#ifndef STATS_H
#define STATS_H

#include <QWidget>

namespace Ui {
class Stats;
}

class Stats : public QWidget
{
    Q_OBJECT

public:
    explicit Stats(QWidget *parent = 0);
    ~Stats();

private slots:
    void on_ok_clicked();

    void on_reset_clicked();

private:
    Ui::Stats *ui;
};

#endif // STATS_H