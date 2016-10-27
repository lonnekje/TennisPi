#ifndef BUTTON_H
#define BUTTON_H

//#include "tpc.h"

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/videoio.hpp"

#include <QWidget>
#include <QLabel>
#include <QMainWindow>
#include <QThread>
#include <QMutex>
#include <QObject>

#include <iostream>
#include <vector>

class Button : public QObject
{

    public:
         Button();
        void virtual ButtonPressed() = 0;
        void virtual ButtonDone() = 0;
        void virtual run() = 0;
};

#endif // BUTTON_H
