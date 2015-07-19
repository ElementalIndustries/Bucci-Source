#ifndef SETTINGS_H
#define SETTINGS_H

#include <QWidget>

namespace Ui {
class Settings;
}

class Settings : public QWidget
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = 0);
    ~Settings();

private slots:
    void on_ok_clicked();

    void on_reset_clicked();

    void on_save_clicked();

    void enableSave();

private:
    Ui::Settings *ui;
};

#endif // SETTINGS_H
