#ifndef PLAY_H
#define PLAY_H


#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/videoio.hpp"

#include "button.h"

#include <QWidget>
#include <QLabel>
#include <QMainWindow>
#include <QThread>
#include <QMutex>
#include <QObject>
#include <QImage>

#include <iostream>
#include <vector>
using namespace cv;


class play : public Button
{

public:
    explicit play();
    void Buttondone();
};

#endif // PLAY_H
