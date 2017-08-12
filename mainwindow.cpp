#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "myopencvsources.h"

#include <QDebug>
#include <QString>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>

using namespace std;
using namespace cv;

myopencvsources a;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    destroyAllWindows();
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    VideoCapture capture(0);
    Mat frame;

    //-- 1. Load the cascades
    if( !a.face_cascade.load( a.face_cascade_name ) )
    {
        printf("--(!)Error loading\n");
        return;
    };
    if( !a.eyes_cascade.load( a.eyes_cascade_name ) )
    {
        printf("--(!)Error loading\n");
        return ;
    };

    if( capture.isOpened() )
    {
        while( true )
        {
            capture.read(frame);

            //-- 3. Apply the classifier to the frame
            if( !frame.empty() )
            {
                a.detectAndDisplay( frame );
            }
            else
            {
                printf(" --(!) No captured frame -- Break!");
                break;
            }

            int c = waitKey(10);
            if( (char)c == 'c' )
            {
                break;
            }
        }
        destroyAllWindows();
    }
    return ;
}

void MainWindow::on_pushButton_2_clicked()
{
    VideoCapture capture(0);
    Mat frame;


    if( capture.isOpened() )
    {
        while( true )
        {
            capture.read(frame);

            //-- 3. Apply the classifier to the frame
            if( !frame.empty() )
            {
                a.imgToEdge(frame);
            }
            else
            {
                printf(" --(!) No captured frame -- Break!");
                break;
            }

            int c = waitKey(10);
            if( (char)c == 'c' )
            {
                break;
            }
        }
        destroyAllWindows();
    }
    return ;
}

void MainWindow::on_pushButton_3_clicked()
{
    VideoCapture capture(0);
    Mat frame;


    if( capture.isOpened() )
    {
        while( true )
        {
            capture.read(frame);

            //-- 3. Apply the classifier to the frame
            if( !frame.empty() )
            {
                corner_src = frame;
                cvtColor( corner_src, corner_gray, CV_BGR2GRAY );
                //                Canny( corner_gray, corner_gray, 90, 400, 3);
                /// Create a window and a trackbar
                namedWindow( corner_source_window, CV_WINDOW_AUTOSIZE );
                imshow( corner_source_window, corner_gray );

                cornerDetect( 0, 0 );
            }
            else
            {
                printf(" --(!) No captured frame -- Break!");
                break;
            }

            int c = waitKey(10);
            if( (char)c == 'c' )
            {
                break;
            }
        }
        destroyAllWindows();
    }
    return ;
}

void MainWindow::on_pushButton_4_clicked()
{

    VideoCapture capture(0);
    Mat frame;


    if( capture.isOpened() )
    {
        while( true )
        {
            capture.read(frame);

            //-- 3. Apply the classifier to the frame
            if( !frame.empty() )
            {
                a.colorDetect(frame);
            }
            else
            {
                printf(" --(!) No captured frame -- Break!");
                break;
            }

            int c = waitKey(10);
            if( (char)c == 'c' )
            {
                break;
            }
        }
        destroyAllWindows();
    }
    return ;
}

void MainWindow::on_pushButton_5_clicked()
{

    VideoCapture capture(0);
    Mat frame;


    if( capture.isOpened() )
    {
        while( true )
        {
            capture.read(frame);

            //-- 3. Apply the classifier to the frame
            if( !frame.empty() )
            {
                a.shapeDetect(frame);
            }
            else
            {
                printf(" --(!) No captured frame -- Break!");
                break;
            }

            int c = waitKey(10);
            if( (char)c == 'c' )
            {
                break;
            }
        }
        destroyAllWindows();
    }
    return ;
}

void MainWindow::on_pushButton_6_clicked()
{
    VideoCapture capture(0);
    Mat frame;

    //-- 1. Load the cascades
    if( !a.face_cascade.load( a.face_cascade_name ) )
    {
        qDebug()<<"--(!)Error loading\n";
        return;
    };
    if( !a.eyes_cascade.load( a.eyes_cascade_name ) )
    {
        qDebug()<<"--(!)Error loading\n";
        return ;
    };

    if( capture.isOpened() )
    {
        while( true )
        {
            capture.read(frame);

            //-- 3. Apply the classifier to the frame
            if( !frame.empty() )
            {
                a.cornerDetect1(frame);
            }
            else
            {
                printf(" --(!) No captured frame -- Break!");
                break;
            }

            int c = waitKey(10);
            if( (char)c == 'c' )
            {
                break;
            }
        }
        destroyAllWindows();
    }
    return ;
}

void MainWindow::on_pushButton_7_clicked()
{
    VideoCapture capture(0);
    Mat frame;

    if( capture.isOpened() )
    {
        while( true )
        {
            capture.read(frame);

            //-- 3. Apply the classifier to the frame
            if( !frame.empty() )
            {
                a.colorDect( frame );
            }
            else
            {
                printf(" --(!) No captured frame -- Break!");
                break;
            }

            int c = waitKey(10);
            if( (char)c == 'c' )
            {
                break;
            }
        }
        destroyAllWindows();
    }
    return ;
}

void MainWindow::cornerDetect( int, void* )
{

    Mat dst, dst_norm, dst_norm_scaled;
    dst = Mat::zeros( corner_src.size(), CV_32FC1 );

    /// Detector parameters
    int blockSize = 2;
    int apertureSize = 3;
    double k = 0.02;

    /// Detecting corners
    cornerHarris( corner_gray, dst, blockSize, apertureSize, k, BORDER_DEFAULT );

    /// Normalizing
    normalize( dst, dst_norm, 0, 255, NORM_MINMAX, CV_32FC1, Mat() );
    convertScaleAbs( dst_norm, dst_norm_scaled );

    Point prePoint;
    int pointCount=0;
    /// Drawing a circle around corners
    for( int j = 0; j < dst_norm.rows ; j++ )
    { for( int i = 0; i < dst_norm.cols; i++ )
        {
            if( (int) dst_norm.at<float>(j,i) > corner_thresh )
            {
                if( cv::norm( cv::Mat(Point(j,i)) , cv::Mat(prePoint) ) > 1 ){
                    circle( dst_norm_scaled, Point( i, j ), 5,  (255,255,255), 2, 8, 0 );
                }
                pointCount++;
                prePoint = Point(j,i);
            }
        }
    }
    QString s = QString::number(pointCount);
    putText(dst_norm_scaled, s.toStdString(), Point(20,30), cv::FONT_HERSHEY_SIMPLEX, 1, Scalar(255,250,0), 2, cv::LINE_AA );
    /// Showing the result
    namedWindow( corner_corners_window, CV_WINDOW_AUTOSIZE );
    imshow( corner_corners_window, dst_norm_scaled );
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    corner_thresh=value;
    ui->label_thresh->setText(QString("Thresh: %1").arg(ui->horizontalSlider->value()));
}

void MainWindow::on_edgeMinSlider_valueChanged(int value)
{
    a.edgeMinSlider = value;
    ui->lbledgeMin->setText(QString("Min: %1").arg(ui->edgeMinSlider->value()));
}

void MainWindow::on_edgeMaxSlider_valueChanged(int value)
{
    a.edgeMaxSlider = value;
    ui->lbledgeMax->setText(QString("Max: %1").arg(ui->edgeMaxSlider->value()));
}

void MainWindow::on_sliderCircleR_valueChanged(int value)
{
    a.colorRadius = value;
    a.colorRadiusToPisc = (int) a.colorRadius*0.7;

    ui->label_color->setText(QString("Radius: %1").arg(ui->sliderCircleR->value()));
}

void MainWindow::on_sliderCorner1_valueChanged(int value)
{
    a.corner1_maxCorners=value;
    ui->lblCorner1->setText(QString("Sens: %1").arg(ui->sliderCorner1->value()));
}

void MainWindow::on_sliderColorB_valueChanged(int value)
{
    a.colorB = value;
    ui->lblColorDectB->setText(QString("B: %1").arg(ui->sliderColorB->value()));
}

void MainWindow::on_sliderColorG_valueChanged(int value)
{
    a.colorG = value;
    ui->lblColorDectG->setText(QString("G: %1").arg(ui->sliderColorG->value()));
}

void MainWindow::on_sliderColorR_valueChanged(int value)
{
    a.colorR = value;
    ui->lblColorDectR->setText(QString("R: %1").arg(ui->sliderColorR->value()));
}

void MainWindow::on_sliderColorLamda_valueChanged(int value)
{
    a.colorLamda = value;
}
