#ifndef SETUP_H
#define SETUP_H

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/videoio.hpp"

#include "button.h"
#include "tpc.h"

#include <unistd.h>

#include <QWidget>
#include <QLabel>
#include <QMainWindow>
#include <QThread>
#include <QMutex>
#include <QObject>
#include <QImage>
#include <QString>
#include <QPushButton>
#include <QPixmap>

#include <iostream>
#include <vector>
using namespace cv;


class Setup : public Button
{
    Q_OBJECT

public:
    explicit Setup();
    void run();

    bool bsStop;

signals:
    void valueChanged(int, QImage);

private:
    int i = 0;
    int j = 0;
    int w = 640;
    int h = 480;
    int y = 0;

};

#endif // SETUP_H
