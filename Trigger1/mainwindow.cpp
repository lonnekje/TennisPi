#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/videoio.hpp"

using namespace cv;
using namespace std;

#define w 640
#define h 480

int i = 0;
int button = 0;

void MyLine(Mat img, Point start, Point end );

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_setupButton_clicked()
{
    button = 0;
    // Initialize capturing live feed from the camera
       CvCapture* capture = 0;

       capture = cvCaptureFromCAM(0);

       // Couldn't get a device? Throw an error and quit
       if(!capture)
       {
           ui->infoLabel->setText("Could not initialize capturing...");
       }

       // The two windows we'll be using
       cvNamedWindow("video");

      // This image holds the "scribble" data...
      // the tracked positions of the ball
      IplImage* imgScribble = NULL;

      // An infinite loop
      while(true)
          {
          // Will hold a frame captured from the camera
          IplImage* frame = 0;
          frame = cvQueryFrame(capture);

          // If we couldn't grab a frame... quit
          if(!frame)
          break;

          // If this is the first frame, we need to initialize it
          if(imgScribble == NULL)
          {
              imgScribble = cvCreateImage(cvGetSize(frame), 8, 3);
          }

          // Draw a yellow line from the previous point to the current point
          cvLine(imgScribble, cvPoint(0, h-40), cvPoint(w, h-40), cvScalar(0,255,255), 5);
          cvLine(imgScribble, cvPoint(0, h-80), cvPoint(w, h-80), cvScalar(0,255,255), 5);
          cvLine(imgScribble, cvPoint(0, h-200), cvPoint(w, h-200), cvScalar(0,255,255), 5);
          cvLine(imgScribble, cvPoint(0, h-190), cvPoint(w, h-190), cvScalar(0,255,255), 5);
          cvLine(imgScribble, cvPoint(0, h), cvPoint(w-400, h-200), cvScalar(0,255,255), 5);
          cvLine(imgScribble, cvPoint(w+80, h), cvPoint(w-160, h-200), cvScalar(0,255,255), 5);



          // Add the scribbling image and the frame...
          cvAdd(frame, imgScribble, frame);
          cvShowImage("video", frame);


          // Wait for a keypress
          int c = cvWaitKey(10);
          if(c!=-1)
          {
              // If pressed, break out of the loop
              break;
          }

          if(button >= 1){
              destroyWindow("video");
              break;
          }

          // Release the thresholded image+moments... we need no memory leaks.. please
          //cvReleaseImage(&imgYellowThresh);
         // delete moments;
          }
      // We're done using the camera. Other applications can now use it
      cvReleaseCapture(&capture);
}


void MainWindow::on_pushButton_clicked()
{
    button = 1;
    ui->infoLabel->setText("Setup done!");
}

void MainWindow::on_startButton_clicked()
{
    //initialise buffer
    ui->infoLabel->setText("Start hitting!");
}
