#-------------------------------------------------
#
# Project created by QtCreator 2016-09-30T11:26:24
#
#-------------------------------------------------

QT       += core gui
TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG += qt

QT_CONFIG -= no-pkg-config
CONFIG += link_pkgconfig
PKGCONFIG += opencv

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TennisPiController
TEMPLATE = app

DEFINES += APP_VERSION=\\\"1.3.2\\\"

SOURCES += main.cpp\
    tennispicontroller.cpp \
    button.cpp \
    setup.cpp

HEADERS  += \
    tennispicontroller.h \
    button.h \
    setup.h \
    ../../Github/opencv/modules/highgui/include/opencv2/highgui.hpp \
    ../../Github/opencv/modules/imgproc/include/opencv2/imgproc.hpp \
    ../../Github/opencv/modules/videoio/include/opencv2/videoio.hpp

FORMS    += \
    mainwindow.ui

QMAKE_CXXFLAGS += -Wall


INCLUDEPATH += ../Github/opencv/include/opencv
INCLUDEPATH += ../Github/opencv/include/opencv2
INCLUDEPATH += /usr/local/include/opencv

LIBS += -L/home/lonneke/Github/opencv/build \
     -lopencv_calib3d\
     -lopencv_core\
     -lopencv_features2d \
     -lopencv_flann\
     -lopencv_highgui\
     -lopencv_imgproc\
     -lopencv_ml\
     -lopencv_objdetect\
     -lopencv_photo\
     -lopencv_stitching\
     -lopencv_superres\
     -lopencv_video\
     -lopencv_videostab
