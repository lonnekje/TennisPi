#include "tennispicontroller.h"
#include "setup.h"
#include "ui_mainwindow.h"


TennisPiController::TennisPiController(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::TennisPiController)
{
    ui->setupUi(this);

    QPushButton *Setupbut = new QPushButton("Setup", this);
    Setupbut->move(10,10);
    connect(Setupbut, SIGNAL(clicked()), this, SLOT(setupSlot()));

    QPushButton *Setupdonebut = new QPushButton("Setup done", this);
    Setupdonebut->move(10, 50);
    connect(Setupdonebut, SIGNAL(clicked()), this, SLOT(setupdoneSlot()));

    ui->acceptDrops()

}

void TennisPiController::setupSlot()
{
    ui->tekstlabel->setText("Button setup clicked");
    //mThread->start();
   // mThread->Stop = false;
    Setup s;
    s.run();


}

void TennisPiController::setupdoneSlot()
{
    //mThread->Stop = true;
    ui->tekstlabel->setText("Button setup done clicked");
    Setup u;
    u.ButtonDone();
}

void TennisPiController::Setimage(QImage &img)
{
    ui->biglabel->setPixmap(QPixmap::fromImage(img));
}



TennisPiController::~TennisPiController()
{
    delete ui;
}
