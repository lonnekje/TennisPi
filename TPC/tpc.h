#ifndef TPC_H
#define TPC_H

#include <QMainWindow>
#include <iostream>
#include <QString>
#include <QLabel>
#include <QPushButton>
#include <QPixmap>
#include <QDialog>
#include "setup.h"
#include "play.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <chrono>
#include <ctime>
#include <wiringPi.h>

namespace Ui {
class TPC;
}

class Setup;
class play;

class TPC : public QMainWindow
{
    Q_OBJECT

public:
    explicit TPC(QWidget *parent = 0);
    Setup *mThread;
    play *pThread;

    std::string getName(){return filename;}


    ~TPC();

public slots:
    void onValueChanged(int, QImage);
    void Triggered();


private slots:
    void setupSlot();
    void setupdoneSlot();

    void playSlot();
    void playdoneSlot();


private:
    int number = 0;
    int state = 0;
    int result = 0;
    Ui::TPC *ui;

    std::string filename;

};

#endif // TPC_H
