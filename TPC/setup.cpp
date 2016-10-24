#include "setup.h"


Setup::Setup()// : Button()
{}


void Setup::run()
{
    std::cout << "Function Button Pressed Setup" << std::endl;
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
    IplImage* imgScribble = NULL;
    IplImage* frame = NULL;

    do {
            i++;
            std::cout <<"i: "<< i << std::endl;
            std::cout <<"j:  " << j << std::endl;

            //Setup s;
           // s.SetTo(Stop);

            // Will hold a frame captured from the camera

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
            //cvResize(frame, frame, Size(482, 301), 0, 0, INTER_LINEAR);
            //cvCvtColor(frame, image, CV_BGR2RGB);




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



            //cvShowImage("Setup", frame);
            TPC tpc;
            tpc.Setimage(*rgbimg);


            // Wait for a keypress
            int c = cvWaitKey(10);
            if(c!=-1)
            {
              // If pressed, break out of the loop
              break;
            }

       /* QMutex mutex;
        // prevent other threads from changing the "Stop" value
        mutex.lock();
        if(this->Stop) break;


        // emit the signal for the count label
        emit valueChanged(rgbimg);
        mutex.unlock();
            if(j==3333)
            {
                break;
            }*/
     } while(i <= 50);

    std::cout << "done " << std::endl;
    //when done
    cv::destroyWindow("Setup");
    // We're done using the camera. Other applications can now use it
    cvReleaseCapture(&capture);
    cvReleaseImage(&frame);

}

void Setup::ButtonDone()
{

    j = 3333;
        std::cout << "j: "<< j << std::endl;
        //msleep(500);

}

void Setup::SetTo(bool &Var)
{
    if(j == 0)
    {Var = false;}
    else
    {Var = true;}
}

