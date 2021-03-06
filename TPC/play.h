#ifndef PLAY_H
#define PLAY_H

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/core/utility.hpp"
#include "opencv2/tracking.hpp"

#include <raspicam/raspicam_cv.h>

#include <boost/circular_buffer.hpp>

#include "button.h"
#include "tpc.h"

#include <unistd.h>
#include <math.h>
#include <ctime>
#include <iostream>
#include <time.h>


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
#include <QTime>


#include <iostream>
#include <vector>

#define BUFFERSIZE 9
#define BUTTON_PIN 0

class play : public Button
{
    Q_OBJECT

    public:
        explicit play();
        void run();
        static void myInterrupt();




        bool Stop = false;
        bool Trig = false;


    signals:
        void valueChanged(int, QImage);

    private:
        int y = 0;
        int i = 0;
        int x = 0;
        int z = 0;

        int posX = 0;
        int posY = 0;
        int iLastX = 0;
        int iLastY = 0;

        int res=0;
        int result = 0;
        int postimg = 0;

        std::string date;
        std::string slash = "/";
        std::string extention = ".jpg";
        std::string temppath = "/home/pi/Desktop/TennisPi/";

        bool firsttime = true;
        bool init = false;
        static bool Trig2;

        // Initialize capturing live feed from the camera
        raspicam::RaspiCam_Cv capture;
        cv::Mat frame;
        cv::Mat input;
        cv::Mat conv;
        cv::Mat HSVimg;
        cv::Mat imgBallTresh;
        cv::Mat canny;
        cv::Mat color;
        cv::Mat gray;
        cv::Mat imgLine;
        cv::Mat post;

        cv::Rect2d roi;




};

#endif // PLAY_H
