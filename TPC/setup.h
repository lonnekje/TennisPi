#ifndef SETUP_H
#define SETUP_H


#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/videoio.hpp"

#include "tpc.h"
#include "button.h"

#include <QWidget>
#include <QLabel>
#include <QMainWindow>
#include <QThread>
#include <QMutex>
#include <QObject>
#include <QImage>

#include <iostream>
#include <vector>
//using namespace cv;




class Setup //: public Button
{
    //Q_OBJECT

public:
    explicit Setup();
    void run();
    void ButtonPressed(void);
    void ButtonDone();
    void SetTo(bool &Var);


signals:
    void valueChanged(const QImage*);


private:
    int i = 0;
    int j = 0;
    int w = 640;
    int h = 480;
    bool Stop = false;

};

#endif // SETUP_H
