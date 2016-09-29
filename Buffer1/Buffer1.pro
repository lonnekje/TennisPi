QT += core gui
TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG += qt

QT_CONFIG -= no-pkg-config
CONFIG += link_pkgconfig
PKGCONFIG += opencv

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Setup
TEMPLATE = app

DEFINES += APP_VERSION=\\\"1.3.2\\\"

SOURCES += main.cpp

HEADERS += cvimagewidget.h


QMAKE_CXXFLAGS += -Wall


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
