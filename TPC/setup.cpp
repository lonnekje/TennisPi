#include "setup.h"
#include "ui_tpc.h"

Setup::Setup(): Button()

{
}

void Setup::run()
{
    // ///////////////////////////////////////////////////////////////////////////////
    // Initialize camera, grab frame
    // ///////////////////////////////////////////////////////////////////////////////

    // Initialize capturing live feed from the camera
    CvCapture* capture = 0;
    capture = cvCaptureFromCAM(0);

    // Couldn't get a device? Throw an error and quit
    if(!capture)
    {
        std::cout << "Could not initialize capturing..." << std::endl;
    }

    // The window
    //cvNamedWindow("Setup");

    // This image holds the "scribble" data...
    //IplImage* imgScribble = NULL;
    IplImage* frame = NULL;

do{

    frame = cvQueryFrame(capture);

    // If we couldn't grab a frame... quit
    if(!frame)
        //break;

    // If this is the first frame, we need to initialize it
    if(frame == NULL)
    {
      frame = cvCreateImage(cvGetSize(frame), 8, 3);
    }
    // ///////////////////////////////////////////////////////////////////////////////
    // Image processing; Drawing lines
    // ///////////////////////////////////////////////////////////////////////////////

   // Draw a yellow line from the previous point to the current point
    cvLine(frame, cvPoint(0, h-40), cvPoint(w, h-40), cvScalar(0,255,255), 5);
    cvLine(frame, cvPoint(0, h-80), cvPoint(w, h-80), cvScalar(0,255,255), 5);
    cvLine(frame, cvPoint(0, h-200), cvPoint(w, h-200), cvScalar(0,255,255), 5);
    cvLine(frame, cvPoint(0, h-190), cvPoint(w, h-190), cvScalar(0,255,255), 5);
    cvLine(frame, cvPoint(0, h), cvPoint(w-400, h-200), cvScalar(0,255,255), 5);
    cvLine(frame, cvPoint(w+80, h), cvPoint(w-160, h-200), cvScalar(0,255,255), 5);


    // ///////////////////////////////////////////////////////////////////////////////
    // Convert Image from IPLImage to QImage
    // ///////////////////////////////////////////////////////////////////////////////

    QImage *rgbimg= new QImage(frame->width, frame->height, QImage::Format_RGB32);

            for (int y=0;y<frame->height;y++)
            {
              unsigned int *dst= (unsigned int*)rgbimg->scanLine(y);
              unsigned char *src= (unsigned char*)frame->imageData + y*frame->width*3;
              for (int x=0;x<frame->width;x++,src+=3)
              {
                *dst++= src[0] | (src[1]<<8) | (src[2]<<16) | (0xff<<24);
              }
            }



        QMutex mutex;
        // prevent other threads from changing the "Stop" value
        mutex.lock();
        if(this->bsStop) break;
        mutex.unlock();

        // emit the signal for the count label
        emit valueChanged(i, *rgbimg);

        // slowdown the count change, msec
        usleep(500);

        // Wait for a keypress
        int c = cvWaitKey(10);
        if(c!=-1)
        {
          // If pressed, break out of the loop
         break;
        }
     }while(bsStop == false);

    // ///////////////////////////////////////////////////////////////////////////////
    // Release capture and image
    // ///////////////////////////////////////////////////////////////////////////////

        cvReleaseCapture(&capture);
        cvReleaseImage(&frame);

}
