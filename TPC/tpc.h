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
    ~TPC();

public slots:
    void onValueChanged(int, QImage);

private slots:
    void setupSlot();
    void setupdoneSlot();

    void playSlot();
    void playdoneSlot();

private:
    int number = 0;
    int state = 0;
    Ui::TPC *ui;
};

#endif // TPC_H
