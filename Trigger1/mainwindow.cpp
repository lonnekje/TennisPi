#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include <vector>

using namespace cv;
using namespace std;

#define w 640
#define h 480

int i = 0;
int button = 0;
int trigger = 0;
int stopbutton = 0;

typedef struct circular_buffer
{
    void *buffer;     // data buffer
    void *buffer_end; // end of data buffer
    size_t capacity = 5;  // maximum number of items in the buffer
    size_t count;     // number of items in the buffer
    size_t sz;        // size of each item in the buffer
    void *head;       // pointer to head
    void *tail;       // pointer to tail
} circular_buffer;


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
    ui->infoLabel->setText("Setup");
    button = 0;
    // Initialize capturing live feed from the camera
       CvCapture* capture = 0;

       capture = cvCaptureFromCAM(0);

       // Couldn't get a device? Throw an error and quit
       if(!capture)
       {
           ui->infoLabel->setText("Could not initialize capturing...");
       }

       // The window
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
    ui->infoLabel->setText("Start!");

    trigger = 0;
    stopbutton = 0;
    // Initialize capturing live feed from the camera
       CvCapture* capture = 0;

       capture = cvCaptureFromCAM(0);

       // Couldn't get a device? Throw an error and quit
       if(!capture)
       {
           ui->infoLabel->setText("Could not initialize capturing...");
       }

       // The window
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

          if(trigger >= 1){

              cvAdd(frame, imgScribble, frame);
              cvShowImage("frame", frame);
              destroyWindow("video");

              break;
          }

          if(stopbutton >= 1){
              destroyWindow("video");
              destroyWindow("frame");
              break;
          }

      }
      // We're done using the camera. Other applications can now use it
      cvReleaseCapture(&capture);
}

void MainWindow::on_triggerButton_clicked()
{
    trigger = 1;
    ui->infoLabel->setText("Trigger!");
}



void MainWindow::on_stopButton_clicked()
{
    stopbutton = 1;
    ui->infoLabel->setText("Done!");
}


void cb_init(circular_buffer *cb, size_t capacity, size_t sz)
{
 cb->buffer = malloc(capacity * sz);
 if(cb->buffer == NULL)
     // handle error
 cb->buffer_end = (char *)cb->buffer + capacity * sz;
 cb->capacity = capacity;
 cb->count = 0;
 cb->sz = sz;
 cb->head = cb->buffer;
 cb->tail = cb->buffer;
}

void cb_free(circular_buffer *cb)
{
 free(cb->buffer);
 // clear out other fields too, just to be safe
}

void cb_push_back(circular_buffer *cb, const void *item)
{
 if(cb->count == cb->capacity)
     // handle error
 memcpy(cb->head, item, cb->sz);
 cb->head = (char*)cb->head + cb->sz;
 if(cb->head == cb->buffer_end)
     cb->head = cb->buffer;
 cb->count++;
}

void cb_pop_front(circular_buffer *cb, void *item)
{
 if(cb->count == 0)
     // handle error
 memcpy(item, cb->tail, cb->sz);
 cb->tail = (char*)cb->tail + cb->sz;
 if(cb->tail == cb->buffer_end)
     cb->tail = cb->buffer;
 cb->count--;
}
