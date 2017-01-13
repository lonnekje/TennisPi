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
    //CvCapture* capture = 0;
    //capture = cvCaptureFromCAM(0);

    cv::VideoCapture capture;
    //capture = new cv::VideoCapture;
    IplImage* frame = NULL;
    Mat cap;

    capture.read(cap);


  /*  RaspiCamCvCapture * capture = raspiCamCvCreateCameraCapture(0);
    cv::Mat image(raspiCamCvQueryFrame(capture));
    cv::namedWindow("Display", CV_WINDOW_AUOSIZE);
    cv::imshow("Display", image);
    cv::waitKey(0)*/


   //IplImage* frame = cvCreateImage(cvSize(640, 480), 8, 3);

    // Couldn't get a device? Throw an error and use image
    /*if(!cap)
    {
        std::cout << "Could not initialize capturing..." << std::endl;
        std::cout<<"Trying to load an image..." <<std::endl;

        frame = cvLoadImage("/home/pi/Desktop/tennis.jpg" , 1);
    }*/


    // The window
    //cvNamedWindow("Output");

    // This image holds the "scribble" data...
    //IplImage* imgScribble = NULL;
   // IplImage* frame = NULL;
    IplImage* imgBallTresh = NULL;
    IplImage* imgHSV = NULL;

    cv::Mat gray;
    cv::Mat canny;
    //IplImage* contours = NULL;


do{
    y++;

   /* if(capture)
    {
        frame = cvQueryFrame(capture);

        // If we couldn't grab a frame... quit
        if(!frame)
            //break;

        // If this is the first frame, we need to initialize it
        if(frame == NULL)
        {
          frame  = cvCreateImage(cvSize(640, 480), 8, 3);
        }
        Mat color(cv::cvarrToMat(frame, false, true, 0, 0));
    if(frame == NULL)
    {
      frame  = cvCreateImage(cvSize(640, 480), 8, 3);
    }

    // ///////////////////////////////////////////////////////////////////////////////
    // Do some image processing here
    // ///////////////////////////////////////////////////////////////////////////////
    // Convert it to gray
       cv::cvtColor( color, gray, CV_BGR2GRAY );

       // compute canny (don't blur with that image quality!!)
       cv::Canny(gray, canny, 200,20);
       //cv::namedWindow("canny2"); cv::imshow("canny2", canny>0);

       std::vector<cv::Vec3f> circles;

       /// Apply the Hough Transform to find the circles
       cv::HoughCircles( gray, circles, CV_HOUGH_GRADIENT, 1, 60, 200, 20, 0, 0 );

       /// Draw the circles detected
       for( size_t i = 0; i < circles.size(); i++ )
       {
           Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
           int radius = cvRound(circles[i][2]);
           cv::circle( color, center, 3, Scalar(0,255,255), -1);
           cv::circle( color, center, radius, Scalar(0,0,255), 1 );
       }

       //compute distance transform:
       cv::Mat dt;
       cv::distanceTransform(255-(canny>0), dt, CV_DIST_L2 ,3);
       cv::namedWindow("distance transform"); cv::imshow("distance transform", dt/255.0f);

       // test for semi-circles:
       float minInlierDist = 2.0f;
       for( size_t i = 0; i < circles.size(); i++ )
       {
           // test inlier percentage:
           // sample the circle and check for distance to the next edge
           unsigned int counter = 0;
           unsigned int inlier = 0;

           cv::Point2f center((circles[i][0]), (circles[i][2]));
           float radius = (circles[i][2]);

           // maximal distance of inlier might depend on the size of the circle
           float maxInlierDist = radius/25.0f;
           if(maxInlierDist<minInlierDist) maxInlierDist = minInlierDist;

           //TODO: maybe paramter incrementation might depend on circle size!
           for(float t =0; t<2*3.14159265359f; t+= 0.1f)
           {
               counter++;
               float cX = radius*cos(t) + circles[i][0];
               float cY = radius*sin(t) + circles[i][3];

               if(dt.at<float>(cY,cX) < maxInlierDist)
               {
                   inlier++;
                   cv::circle(color, cv::Point2i(cX,cY),3, cv::Scalar(0,255,0));
               }
              else
                   cv::circle(color, cv::Point2i(cX,cY),3, cv::Scalar(255,0,0));
           }
           std::cout << 100.0f*(float)inlier/(float)counter << " % of a circle with radius " << radius << " detected. Loop:  " << y << std::endl;
       }

       cv::imshow("Output", color);*/


    //imgHSV = cvCreateImage(cvSize(640, 480), 8, 3);
    //cvCvtColor(frame, imgHSV, CV_RGB2HSV);  //right color conversion?

    //imgBallTresh = cvCreateImage(cvSize(640, 480), 8, 1);

    //cvInRangeS(imgHSV, CvScalar(30,90,130), CvScalar(40,255,255), imgBallTresh);



    Mat imageThreshMat(cv::cvarrToMat(imgBallTresh, false, true, 0, 0));
    Mat frameMat(cv::cvarrToMat(frame, false, true, 0, 0));


    GaussianBlur(imageThreshMat,imageThreshMat,Size(9,9),2,2);


    cv::erode(imageThreshMat, imageThreshMat, Mat(), Point(-1, -1), 2, 1, 1 );
    cv::dilate(imageThreshMat, imageThreshMat, Mat(), Point(-1, -1), 2, 1, 1);

    cv::dilate(imageThreshMat, imageThreshMat, Mat(), Point(-1, -1), 2, 1, 1);
    cv::erode(imageThreshMat, imageThreshMat, Mat(), Point(-1, -1), 2, 1, 1 );



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
    //cvReleaseCapture(&capture);
    cvReleaseImage(&frame);


}
