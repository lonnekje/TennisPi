#ifndef PLAY_H
#define PLAY_H

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



class play : public Button
{
    //Q_OBJECT
public:
    explicit play(QObject *parent = 0);
    void Buttondone(){};
};

#endif // PLAY_H
