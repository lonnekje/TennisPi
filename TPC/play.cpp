#include "play.h"

play::play() : Button()
{

}

void play::run()
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
    cvNamedWindow("Control");

    // This image holds the "scribble" data...
    //IplImage* imgScribble = NULL;
    IplImage* frame = NULL;
    IplImage* imgBallTresh = NULL;
    IplImage* imgHSV = NULL;
    //IplImage* contours = NULL;


do{

    frame = cvQueryFrame(capture);

    // If we couldn't grab a frame... quit
    if(!frame)
        //break;

    // If this is the first frame, we need to initialize it
    if(frame == NULL)
    {

      frame  = cvCreateImage(cvSize(640, 480), 8, 3);
    }




    // ///////////////////////////////////////////////////////////////////////////////
    // Do some image processing here
    // ///////////////////////////////////////////////////////////////////////////////
    imgBallTresh = cvCreateImage(cvGetSize(frame), 8, 1);

    imgHSV = cvCreateImage(cvGetSize(frame), 8, 3);
    cvCvtColor(frame, imgHSV, CV_BGR2HSV);


    cvInRangeS(imgHSV, CvScalar(30,130,130), CvScalar(60,255,255), imgBallTresh);



    Mat imageThreshMat(cv::cvarrToMat(imgBallTresh, false, true, 0, 0));
    Mat frameMat(cv::cvarrToMat(frame, false, true, 0, 0));


    GaussianBlur(imageThreshMat,imageThreshMat,Size(9,9),2,2);


    // Find the contours.
    std::vector<std::vector<cv::Point> > contours;
    std::vector< Vec4i > hierarchy;

    cv::Mat contourOutput = imageThreshMat.clone();
    cv::findContours( contourOutput, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE );


    //Draw the contours
    cv::Mat contourImage = frameMat.clone();

    int count = 0;

    for (size_t idx = 0; idx < contours.size(); idx++)
    {
       //cv::drawContours(contourImage, contours, idx, cv::Scalar(255, 0, 0));

        Rect r= boundingRect(contours[i]);
        if(hierarchy[i][2]<0){
            rectangle(contourImage,Point(r.x,r.y), Point(r.x+r.width,r.y+r.height), Scalar(0,0,255),3,8,0);
            count++;
        }
    }


    std::vector<Vec3f> circles;

    /// Apply the Hough Transform to find the circles
    HoughCircles( imageThreshMat, circles, CV_HOUGH_GRADIENT, 1, imageThreshMat.rows/8, 200, 100, 0, 0 );

    /// Draw the circles detected
    for( size_t i = 0; i < circles.size(); i++ )
    {
        Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
        int radius = cvRound(circles[i][2]);
        // circle center
        circle( contourImage, center, 3, Scalar(0,255,0), -1, 8, 0 );
        // circle outline
        circle( contourImage, center, radius, Scalar(0,0,255), 3, 8, 0 );
    }


    cv::imshow("Control", imageThreshMat);
    cv::imshow("video", contourImage);
    // ///////////////////////////////////////////////////////////////////////////////
    // Find ball position
    // ///////////////////////////////////////////////////////////////////////////////


    CvMoments *moments = (CvMoments*)malloc(sizeof(CvMoments));

    cvMoments(imgBallTresh, moments, 1);

    // The actual moment values
    double moment10 = cvGetSpatialMoment(moments, 1, 0);
    double moment01 = cvGetSpatialMoment(moments, 0, 1);

    double area = cvGetCentralMoment(moments, 0, 0);

    // Holding the last and current ball positions
    static int posX = 0;

    static int posY = 0;

    int lastX = posX;

    int lastY = posY;

    posX = moment10/area;
    posY = moment01/area;

    // ///////////////////////////////////////////////////////////////////////////////
    // Do math
    // ///////////////////////////////////////////////////////////////////////////////


    // only use a valid position
    if(lastX>0 && lastY>0 && posX>0 && posY>0)
    {

        // Print it out for debugging purposes
        //printf("position (%d,%d)", posX, posY);


        // Draw a yellow line from the previous point to the current point
        cvLine(frame, cvPoint(posX, posY), cvPoint(lastX, lastY), cvScalar(0,255,255), 5);

        int movedX = lastX - posX;
        int movedY = lastY - posY;

        if(movedX == 0)
        {movedX = movedX++;}

        if(movedY == 0)
        {movedY = movedY++;}

        // ///////////////////////////////////////////////////////////////////////////////
        // STILL NEED TO IMPLEMENT CONVERSION PX TO M
        // let's say 600px and 6m court
        // ///////////////////////////////////////////////////////////////////////////////

        movedY = movedY*movedY;
        movedX = movedX*movedX;

        float result = (sqrt(movedY + movedX))/100;

        if(result < 0)
        {result=result*-1;}


        int speed = (result/0.033);


        std::cout << movedX <<", "<< movedY  <<", "<< speed <<", km/h "<< result << std::endl;



    }



    // ///////////////////////////////////////////////////////////////////////////////
    // Convert image from IPLImage to QImage
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
        if(this->Stop) break;
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


        delete moments;

     }while(Stop == false);


// ///////////////////////////////////////////////////////////////////////////////
// Release capture and image
// ///////////////////////////////////////////////////////////////////////////////
    cvReleaseImage(&imgBallTresh);
    cvReleaseImage(&imgHSV);
    cvReleaseCapture(&capture);
    cvReleaseImage(&frame);


}
