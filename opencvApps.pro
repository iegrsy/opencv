#-------------------------------------------------
#
# Project created by QtCreator 2017-08-01T10:13:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = opencvApps
TEMPLATE = app

INCLUDEPATH += /usr/local/include/opencv

LIBS += -L/usr/local/lib \
-lopencv_ml \
-lopencv_objdetect \
-lopencv_shape\
-lopencv_stitching\
-lopencv_superres\
-lopencv_videostab\
-lopencv_calib3d\
-lopencv_features2d\
-lopencv_highgui\
-lopencv_videoio\
-lopencv_imgcodecs\
-lopencv_video\
-lopencv_photo\
-lopencv_imgproc\
-lopencv_flann\
-lopencv_core


SOURCES += main.cpp\
        mainwindow.cpp \
    myopencvsources.cpp

HEADERS  += mainwindow.h \
    myopencvsources.h

FORMS    += mainwindow.ui


