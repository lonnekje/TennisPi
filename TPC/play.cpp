#include "play.h"

play::play() : Button()
{

}

void play::run()
{
    // ///////////////////////////////////////////////////////////////////////////////
    // Initialize camera, grab frame
    // ///////////////////////////////////////////////////////////////////////////////

    capture.set(CV_CAP_PROP_FORMAT, CV_8UC4);


    // Couldn't get a device? Throw an error and use image
    if(!capture.open())
    {
        std::cout << "Could not initialize capturing..." << std::endl;

        //std::cout<<"Trying to load an image..." <<std::endl;

        //frame = cvLoadImage("/home/pi/Desktop/tennis.jpg" , 1);
    }


    // ///////////////////////////////////////////////////////////////////////////////
    // Initialize buffer
    // ///////////////////////////////////////////////////////////////////////////////

    boost::circular_buffer<Mat> buffer(BUFFERSIZE);

do{
    capture.grab();
    capture.retrieve(input);

    i++;

    cv::resize(input, frame, Size(640,480));


    // ///////////////////////////////////////////////////////////////////////////////
    // Circulair buffer implementation
    // ///////////////////////////////////////////////////////////////////////////////

    buffer.push_back(frame);


    if(Trig)
       {

        QTime myTimer;
        myTimer.start();

            std::chrono::time_point<std::chrono::high_resolution_clock> time;
            time = std::chrono::system_clock::now();
            std::time_t timeNow = std::chrono::system_clock::to_time_t(time);

            std::cout << std::ctime(&timeNow ) << std::endl;
            std::string timed = std::ctime(&timeNow);

            timed.resize(19);

            date = timed;

            date.resize(10);

            std::cout << "Date:" << date << std::endl;

            std::string folderDate = temppath + date;
            const char *d = folderDate.c_str();
            res = mkdir(d, 0777);

                std::string folderName= temppath + date + slash + timed;
                const char *c = folderName.c_str();
                result = mkdir(c, 0777);

                if(result == 0)
                {

                    for(x=0;x<BUFFERSIZE;x++)
                    {
                       // ///////////////////////////////////////////////////////////////////////////////
                        // Making filename
                        // ///////////////////////////////////////////////////////////////////////////////
                        std::string number = std::to_string(x);
                        std::string imgName = temppath + date + slash + timed + slash + timed + number + extention;

                        std::cout << "Image name is: " << imgName << std::endl;

                        // ///////////////////////////////////////////////////////////////////////////////
                        // Do some image processing here
                        // Frame to use buffer[x]
                        // ///////////////////////////////////////////////////////////////////////////////

                        cv::cvtColor(buffer[x], HSVimg, COLOR_RGB2HSV);
                        cv::inRange(HSVimg, Scalar(29,86,90), Scalar(64,255,255), imgBallTresh);

                        cv::erode(imgBallTresh, imgBallTresh, getStructuringElement(MORPH_ELLIPSE, Size(5,5)));
                        cv::dilate(imgBallTresh, imgBallTresh, getStructuringElement(MORPH_ELLIPSE, Size(5,5)));
                        cv::dilate(imgBallTresh, imgBallTresh, getStructuringElement(MORPH_ELLIPSE, Size(5,5)));
                        cv::erode(imgBallTresh, imgBallTresh, getStructuringElement(MORPH_ELLIPSE, Size(5,5)));

                        cv::Moments oMoments = moments(imgBallTresh);

                        double dM01=oMoments.m01;
                        double dM10=oMoments.m10;
                        double dArea = oMoments.m00;

                        if(dArea > 10000)
                        {
                            posX = dM10/dArea;
                            posY = dM01/dArea;

                            if(iLastX >= 0 && iLastY >= 0 && posX >= 0 && posY >= 0)
                            {
                                cv::line(imgLine, Point(posX, posY), Point(0, 0), Scalar(0,0,255), 2);
                            }

                            iLastX=posX;
                            iLastY=posY;
                        }

                        std::cout << "Xpos = " << posX << "Ypos = " << posY << std::endl;


                        input = input + imgLine;




                        // ///////////////////////////////////////////////////////////////////////////////
                        // Saving ONE frame from buffer
                        // ///////////////////////////////////////////////////////////////////////////////
                        cv::imwrite(imgName, input);


                    }

                    Trig=false;
                }
                else
                {std::cout << "Could NOT make a folder, canceled." << std::endl;}

                int nMilliseconds = myTimer.elapsed();

                std::cout << "Trigger process time: " << nMilliseconds << std::endl;
        }

    //frame=buffer[0];

    //cvtColor(input, frame, CV_RGB2BGR);

    cv::resize(input, frame, Size(640,480));


    // ///////////////////////////////////////////////////////////////////////////////
    // Convert image from Mat to QImage
    // ///////////////////////////////////////////////////////////////////////////////

        QImage rgbimg = QImage((uchar*)frame.data, frame.cols, frame.rows, frame.step, QImage::Format_RGB888);


        QMutex mutex;
        // prevent other threads from changing the "Stop" value
        mutex.lock();
        if(this->Stop) break;
        mutex.unlock();

        // emit the signal for the count label & image
        emit valueChanged(i, rgbimg);

        if(waitKey(1) >= 0) break;

        if(i>20000)
        {
            i=0;
            y++;
        }


     }while(Stop == false);

    std::cout << "Amount of frames " << i << " And y " << y << std::endl;


// ///////////////////////////////////////////////////////////////////////////////
// Release capture and image
// ///////////////////////////////////////////////////////////////////////////////

    capture.release();

}
