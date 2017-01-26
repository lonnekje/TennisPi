#include "play.h"

bool play::Trig2;

play::play() : Button()
{

}

void play::myInterrupt()
{
    play::Trig2 = true;
    delayMicroseconds(1500);
    std::cout << "Trig is set to " << Trig2 << std::endl;

}

void play::run()
{



    // ///////////////////////////////////////////////////////////////////////////////
    // Initialize camera, grab frame
    // ///////////////////////////////////////////////////////////////////////////////

    capture.set(CV_CAP_PROP_FORMAT, CV_8UC4);

    std::cout << "FPS: " << capture.get(CV_CAP_PROP_FPS) << std::endl;


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

    // ///////////////////////////////////////////////////////////////////////////////
    // Initialize Interrupt Trigger
    // ///////////////////////////////////////////////////////////////////////////////
    if (!init)
    {
        if(wiringPiSetup()<0)
            {
                fprintf(stderr, "unable to setup WiringPi: %s\n", strerror(errno));
                init=true;
            }

    }



    if (wiringPiISR(BUTTON_PIN, INT_EDGE_FALLING, &myInterrupt) < 0)
        {
            fprintf(stderr, "unable to setup ISR: %s\n", strerror(errno));
        }



do{

        QTime mTimer;
        mTimer.start();

        capture.grab();
        capture.retrieve(input);

        i++;

        cv::resize(input, frame, Size(600,450));


        // ///////////////////////////////////////////////////////////////////////////////
        // Circulair buffer implementation
        // ///////////////////////////////////////////////////////////////////////////////

        buffer.push_back(frame);
        //std::cout << "Trig in func: " << Trig2 << std::endl;
        int nMseconds = mTimer.elapsed();

        //std::cout << "Trigger process time: " << nMseconds << std::endl;

        if(Trig || Trig2)
           {
            postimg = (BUFFERSIZE - 1) / 2;

            for(int r=0;r<postimg;r++)
            {
                capture.grab();
                capture.retrieve(input);
                cv::resize(input, frame, Size(600,450));
                buffer.push_back(frame);
            }

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



                            cv::cvtColor(buffer[x], gray, COLOR_RGB2GRAY);


                            /*std::vector<cv::Vec3f> circles;

                            cv::HoughCircles(gray, circles, CV_HOUGH_GRADIENT,

                                             1, //Accumulator resolution(size of the image / 2)
                                             1, //Minimum distance between two circles
                                             100, // Canny high threshold
                                             15, // Minimum number of votes
                                             4, 10); //Minimum and maximum radius

                            std::cout << "Amount of circles: " << circles.size() << std::endl;

                            std::vector<cv::Vec3f>::const_iterator itc = circles.begin();

                            while(itc!=circles.end()){
                                cv::circle(gray,
                                           cv::Point((*itc)[0], (*itc)[1]), //circle centre
                                           (*itc)[2],                       //circle radius
                                           cv::Scalar(0, 255, 255),         //Color
                                           2);                              //Line thickness

                            std::cout << "X: " << (*itc)[0] << " Y: " << (*itc)[1] << " Radius: " << (*itc)[2] << std::endl;

                                itc++;
                            }*/


                            // ///////////////////////////////////////////////////////////////////////////////
                            // Saving ONE frame from buffer
                            // ///////////////////////////////////////////////////////////////////////////////
                            cv::imwrite(imgName, gray);


                        }

                        Trig=false;
                        Trig2=false;
                    }
                    else
                    {std::cout << "Could NOT make a folder, canceled." << std::endl;}

                    int nMilliseconds = myTimer.elapsed();

                    std::cout << "Trigger process time: " << nMilliseconds << std::endl;
            }

        //frame=buffer[0];

        //cvtColor(input, frame, CV_RGB2BGR);

       cv::resize(buffer[0], frame, Size(640,480));


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
