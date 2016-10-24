#ifndef TENNISPICONTROLLER_H
#define TENNISPICONTROLLER_H

#include <iostream>
#include <QString>
#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QPixmap>
#include "ui_mainwindow.h"

namespace Ui {
class TennisPiController: public QMainWindow{};

}

class Setup;

#define START  0
#define SETUP  1
#define STOPSETUP 2
#define PLAY 3

class TennisPiController : public QMainWindow
{
    Q_OBJECT
public:

    explicit TennisPiController(QWidget *parent = 0);
    void Setimage(QImage &img);

    ~TennisPiController();

    //Setup *mThread;

public slots:

    void onValueChanged(QImage &);

private slots:
    void setupSlot();
    void setupdoneSlot();


private:
    Ui::TennisPiController *ui;
    std::string sWhatsThis = "This is a button";
    int number = 0;


};

#endif // TENNISPICONTROLLER_H
