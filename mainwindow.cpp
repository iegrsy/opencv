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
                edge_src = frame;
                cvtColor( edge_src, edge_gray, CV_BGR2GRAY );
                //                Canny( edge_gray, edge_gray, 90, 400, 3);
                /// Create a window and a trackbar
                namedWindow( edge_source_window, CV_WINDOW_AUTOSIZE );
                imshow( edge_source_window, edge_gray );

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

void MainWindow::cornerDetect( int, void* )
{

    Mat dst, dst_norm, dst_norm_scaled;
    dst = Mat::zeros( edge_src.size(), CV_32FC1 );

    /// Detector parameters
    int blockSize = 2;
    int apertureSize = 3;
    double k = 0.04;

    /// Detecting corners
    cornerHarris( edge_gray, dst, blockSize, apertureSize, k, BORDER_DEFAULT );

    /// Normalizing
    normalize( dst, dst_norm, 0, 255, NORM_MINMAX, CV_32FC1, Mat() );
    convertScaleAbs( dst_norm, dst_norm_scaled );

    /// Drawing a circle around corners
    for( int j = 0; j < dst_norm.rows ; j++ )
    { for( int i = 0; i < dst_norm.cols; i++ )
        {
            if( (int) dst_norm.at<float>(j,i) > edge_thresh )
            {
                circle( dst_norm_scaled, Point( i, j ), 5,  Scalar(0), 2, 8, 0 );
            }
        }
    }
    /// Showing the result
    namedWindow( edge_corners_window, CV_WINDOW_AUTOSIZE );
    imshow( edge_corners_window, dst_norm_scaled );
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    edge_thresh=value;
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


