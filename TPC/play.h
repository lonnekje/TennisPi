#ifndef PLAY_H
#define PLAY_H

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/videoio.hpp"

#include "button.h"
#include "tpc.h"

#include <unistd.h>
#include <math.h>

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


class play : public Button
{
    Q_OBJECT

    public:
        explicit play();
        void run();

        bool Stop;

    signals:
        void valueChanged(int, QImage);

    private:
        int iLowH = 26;
        int iHighH = 179;

        int iLowS = 0;
        int iHighS = 255;

        int iLowV = 170;
        int iHighV = 255;

        int y = 0;
        int i = 0;
        int h= 460;
        int w = 600;
};

#endif // PLAY_H
