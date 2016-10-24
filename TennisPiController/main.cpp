#include "tennispicontroller.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TennisPiController w;
    w.show();


    return a.exec();

}
