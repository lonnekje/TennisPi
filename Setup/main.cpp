
#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/videoio.hpp"

using namespace cv;
using namespace std;

#define w 640
#define h 480

void MyLine(Mat img, Point start, Point end );

 int main( int argc, char** argv )
 {
//Capture the video from camera
    VideoCapture cap(0);
    cap.set(CV_CAP_PROP_FRAME_WIDTH, 640);
    cap.set(CV_CAP_PROP_FRAME_HEIGHT, 480);

    if ( !cap.isOpened() )  // if not success, exit program
    {
         cout << "Cannot open the web cam" << endl;
         return -1;
    }


    while (true)
    {
        Mat imgOriginal;

        bool bSuccess = cap.read(imgOriginal); // read a new frame from video

         if (!bSuccess) //if not success, break loop
        {
             cout << "Cannot read a frame from video stream" << endl;
             break;
        }

  Mat imgLine;

  cvtColor(imgOriginal, imgLine, COLOR_BGR2BGRA); //Convert the captured frame from BGR to HSV


  MyLine( imgLine, Point( 0, h-40), Point( w, h-40 ) );
  MyLine( imgLine, Point( 0, h-80), Point( w, h-80 ) );
  MyLine( imgLine, Point( 0, h-200), Point( w, h-200) );
  MyLine( imgLine, Point( 0, h-190), Point( w, h-190) );
  MyLine( imgLine, Point( 0, h ), Point( w-400, h-200 ) );
  MyLine( imgLine, Point( w+80, h ), Point( w-160, h-200 ) );



  imshow("Line Image", imgLine); //show the thresholded image
  imshow("Original", imgOriginal); //show the original image

        if (waitKey(30) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
       {
            cout << "esc key is pressed by user" << endl;
            break;
       }
    }

   return 0;

}


 void MyLine( Mat img, Point start, Point end )
 {
   int thickness = 2;
   int lineType = 8;
   line( img,
         start,
         end,
         Scalar( 0, 0, 0 ),
         thickness,
         lineType );
 }
