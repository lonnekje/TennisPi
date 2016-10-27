#include "tpc.h"
#include "ui_tpc.h"

TPC::TPC(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TPC)
{
    ui->setupUi(this);


    QPushButton *Setupbut = new QPushButton("Setup", this);
    Setupbut->move(10,10);
    //Setupbut->isEnabled()
    connect(Setupbut, SIGNAL(clicked()), this, SLOT(setupSlot()));

    QPushButton *Setupdonebut = new QPushButton("Setup done", this);
    Setupdonebut->move(10, 50);
    connect(Setupdonebut, SIGNAL(clicked()), this, SLOT(setupdoneSlot()));
}

void TPC::setupSlot()
{
     ui->Textlabel->setText("Button setup clicked");
    Setup s;
    s.run();


}

void TPC::setupdoneSlot()
{
    //mThread->Stop = true;
    ui->Textlabel->setText("Button setup done clicked");
    Setup u;
    u.ButtonDone();
}




TPC::~TPC()
{
    delete ui;
}
