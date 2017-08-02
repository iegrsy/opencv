#ifndef MYOPENCVSOURCES_H
#define MYOPENCVSOURCES_H


#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core.hpp"

#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;
using namespace cv;

class myopencvsources
{
public:

    /** Global variables */
    String face_cascade_name = "/home/ieg/Belgeler/openCV/opencv/data/haarcascades_cuda/haarcascade_frontalface_alt.xml";
    String eyes_cascade_name = "/home/ieg/Belgeler/openCV/opencv/data/haarcascades_cuda/haarcascade_eye_tree_eyeglasses.xml";
    CascadeClassifier face_cascade;
    CascadeClassifier eyes_cascade;
    string window_name = "Capture - Face detection";
    string window_name1 = "Capture - Edge Video";
    string window_name2 = "Capture - Color";
    string window_name3 = "Capture - shape ";
    //     RNG rng(12345);

    int edgeMinSlider = 50;
    int edgeMaxSlider = 200;



    myopencvsources();
    void detectAndDisplay(Mat frame);
    void imgToEdge(Mat frame);
    void colorDetect(Mat frame);



    Mat gray;
    Mat bw;
    Mat dst;
    vector<vector<Point> > contours;
    vector<Point> approx;

    void shapeDetect(Mat frame);
    double angle(Point pt1, Point pt2, Point pt0);
    void setLabel(Mat &im, const string label, vector<Point> &contour);
};

#endif // MYOPENCVSOURCES_H
