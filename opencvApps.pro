#-------------------------------------------------
#
# Project created by QtCreator 2017-08-01T10:13:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = opencvApps
TEMPLATE = app

INCLUDEPATH += C:\openCV\opencv\build\include
INCLUDEPATH += C:\openCV\opencv\build\include\opencv2

LIBS += C:\openCV\opencv\build\x64\vc14\lib\opencv_world320.lib
LIBS += C:\openCV\opencv\build\x64\vc14\lib\opencv_world320d.lib


SOURCES += main.cpp\
        mainwindow.cpp \
    myopencvsources.cpp

HEADERS  += mainwindow.h \
    myopencvsources.h

FORMS    += mainwindow.ui


