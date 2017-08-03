#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    /// Global variables
    Mat corner_src, corner_gray;
    int corner_thresh = 200;
    int corner_max_thresh = 255;

    char* corner_source_window = "Source image";
    char* corner_corners_window = "Corners detected";

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void cornerDetect(int, void *);

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_horizontalSlider_valueChanged(int value);
    void on_edgeMinSlider_valueChanged(int value);
    void on_edgeMaxSlider_valueChanged(int value);
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();

    void on_sliderCircleR_valueChanged(int value);

    void on_pushButton_6_clicked();

    void on_sliderCorner1_valueChanged(int value);

    void on_pushButton_7_clicked();

    void on_sliderColorB_valueChanged(int value);

    void on_sliderColorG_valueChanged(int value);

    void on_sliderColorR_valueChanged(int value);

    void on_sliderColorLamda_valueChanged(int value);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
