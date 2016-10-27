#ifndef SETUP_H
#define SETUP_H


#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/videoio.hpp"

#include "button.h"
#include "tpc.h"

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
    void ButtonPressed(void){};
    void ButtonDone();

private:
    int i = 0;
    int j = 0;
    int w = 640;
    int h = 480;
    bool Stop = false;

};

#endif // SETUP_H
