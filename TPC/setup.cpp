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
    raspicam::RaspiCam_Cv capture;
    Mat frame;
    Mat conv;
    Mat src;

    capture.set(CV_CAP_PROP_FORMAT, CV_8UC4);


    // Couldn't get a device? Throw an error and use image
    if(!capture.open())
    {
        std::cout << "Could not initialize capturing..." << std::endl;
        //std::cout<<"Trying to load an image..." <<std::endl;

        //frame = cvLoadImage("/home/pi/Desktop/tennis.jpg" , 1);
    }



do{
        capture.grab();
        capture.retrieve(src);
        //cv::cvtColor(conv, frame, CV_RGB2BGR);
        cv::resize(src, frame, Size(640,480));

    // ///////////////////////////////////////////////////////////////////////////////
    // Image processing; Drawing lines
    // ///////////////////////////////////////////////////////////////////////////////

   // Draw a yellow line from the previous point to the current point
    cv::line(frame, cvPoint(0, h-40), cvPoint(w, h-40), cvScalar(255,255,0), 5);
    cv::line(frame, cvPoint(0, h-80), cvPoint(w, h-80), cvScalar(255,255,0), 5);
    cv::line(frame, cvPoint(0, h-200), cvPoint(w, h-200), cvScalar(255,255,0), 5);
    cv::line(frame, cvPoint(0, h-190), cvPoint(w, h-190), cvScalar(255,255,0), 5);
    cv::line(frame, cvPoint(0, h), cvPoint(w-400, h-200), cvScalar(255,255,0), 5);
    cv::line(frame, cvPoint(w+80, h), cvPoint(w-160, h-200), cvScalar(255,255,0), 5);




    // ///////////////////////////////////////////////////////////////////////////////
    // Convert Image from IPLImage to QImage
    // ///////////////////////////////////////////////////////////////////////////////

    QImage rgbimg = QImage((uchar*)frame.data, frame.cols, frame.rows, frame.step, QImage::Format_RGB888);

    QMutex mutex;
    // prevent other threads from changing the "Stop" value
    mutex.lock();
    if(this->bsStop) break;
    mutex.unlock();

    // emit the signal for the count label
    emit valueChanged(i, rgbimg);

     // Wait for a keypress
    if(waitKey(1) >= 0) break;

     }while(bsStop == false);

    // ///////////////////////////////////////////////////////////////////////////////
    // Release capture and image
    // ///////////////////////////////////////////////////////////////////////////////

        capture.release();

}
