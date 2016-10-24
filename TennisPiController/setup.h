#ifndef SETUP_H
#define SETUP_H

#include "button.h"
#include "tennispicontroller.h"

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/videoio.hpp"

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

class Button;

class Setup : public Button
{
    Q_OBJECT

public:
    explicit Setup(QObject *parent = 0, bool b = false);
    void run();
    void ButtonPressed(void){};
    void ButtonDone();
    void SetTo(bool &Var);


signals:
    //void valueChanged(const QImage*);


private:
    int i = 0;
    int j = 0;
    int w = 640;
    int h = 480;
    bool Stop = false;

};

#endif // SETUP_H
