#ifndef TPC_H
#define TPC_H

#include <QMainWindow>
#include <iostream>
#include <QString>
#include <QLabel>
#include <QPushButton>
#include <QPixmap>
#include "button.h"
#include "setup.h"


namespace Ui {
class TPC;
}

class Setup;

class TPC : public QMainWindow
{
    Q_OBJECT

public:
    explicit TPC(QWidget *parent = 0);
    void Setimage(QImage &img);
    ~TPC();

public slots:

    //void onValueChanged(QImage &);

private slots:
    void setupSlot();
    void setupdoneSlot();



private:
    int number = 0;
    Ui::TPC *ui;
};

#endif // TPC_H
