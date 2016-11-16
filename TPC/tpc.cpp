#include "tpc.h"
#include "ui_tpc.h"

TPC::TPC(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TPC)
{
    ui->setupUi(this);


    QPushButton *Setupbut = new QPushButton("SETUP", this);
    Setupbut->move(10,20);
    connect(Setupbut, SIGNAL(clicked()), this, SLOT(setupSlot()));


    QPushButton *Setupdonebut = new QPushButton("SETUP DONE", this);
    Setupdonebut->move(10, 50);
    connect(Setupdonebut, SIGNAL(clicked()), this, SLOT(setupdoneSlot()));

    QPushButton *Playbut = new QPushButton("PLAY", this);
    Playbut->move(10,80);
    connect(Playbut, SIGNAL(clicked()), this, SLOT(playSlot()));

    QPushButton *Playdonebut = new QPushButton("PLAY DONE", this);
    Playdonebut->move(10, 110);
    connect(Playdonebut, SIGNAL(clicked()), this, SLOT(playdoneSlot()));


    // create an instance of Setup and Play
    mThread = new Setup();
    pThread = new play();

    // connect signal/slot
    connect(mThread, SIGNAL(valueChanged(int, QImage)),
            this, SLOT(onValueChanged(int, QImage)));

    connect(pThread, SIGNAL(valueChanged(int, QImage)),
            this, SLOT(onValueChanged(int,QImage)));
}

void TPC::onValueChanged(int count, QImage img)
{
    ui->Textlabel->setText(QString::number(count));
    ui->imglabel->setPixmap(QPixmap::fromImage(img));
}

void TPC::setupSlot()
{
    std::cout << "Function Button Pressed Setup" << std::endl;
    mThread->bsStop = false;
    mThread->run();

}

void TPC::setupdoneSlot()
{
    std::cout << "Function Button Pressed Setup Done" << std::endl;
    mThread->bsStop = true;
    ui->imglabel->clear();

}

void TPC::playSlot()
{
    std::cout << "Function Button Pressed Play" << std::endl;
    pThread->Stop = false;
    pThread->run();

}

void TPC::playdoneSlot()
{
    std::cout << std::endl << "Function Button Pressed Play Done" << std::endl;
    pThread->Stop = true;
    ui->imglabel->clear();

}




TPC::~TPC()
{
    delete ui;
}
