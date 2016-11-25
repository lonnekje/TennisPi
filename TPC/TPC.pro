#-------------------------------------------------
#
# Project created by QtCreator 2016-10-20T10:28:50
#
#-------------------------------------------------
QT       += core gui
TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG += qt

CONFIG -= no-pkg-config
CONFIG += link_pkgconfig
PKGCONFIG += opencv

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TPC
TEMPLATE = app

target.path = /home/TPC
INSTALLS += target


DEFINES += APP_VERSION=\\\"1.3.2\\\"

SOURCES += main.cpp\
        tpc.cpp \
    button.cpp \
    setup.cpp \
    play.cpp

HEADERS  += tpc.h \
    button.h \
    setup.h\
    ../../opencv/opencv/modules/highgui/include/opencv2/highgui.hpp \
    ../../opencv/opencv/modules/imgproc/include/opencv2/imgproc.hpp \
    ../../opencv/opencv/modules/videoio/include/opencv2/videoio.hpp \
    play.h

    play.h

FORMS    += tpc.ui


QMAKE_CXXFLAGS += -Wall

 INCLUDEPATH += /home/lonneke/opencv/opencv/modules
#INCLUDEPATH += ../opencv/opencv/include/opencv
#INCLUDEPATH += ../opencv/opencv/include/opencv2
#INCLUDEPATH += /usr/local/include/opencv

LIBS += -L/home/lonneke/opencv/opencv/platforms/linux/build \
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
