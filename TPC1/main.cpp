#include "tpc.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TPC w;
    w.show();

    return a.exec();
}
