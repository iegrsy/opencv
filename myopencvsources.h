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
    string window_name = "Capture - Face detection";
    string window_name1 = "Capture - Edge Video";
    string window_name2 = "Capture - Color";
    string window_name3 = "Capture - shape ";
    string window_name4 = "Capture - corner1";

    String face_cascade_name = "/home/ieg/Belgeler/openCV/opencv/data/haarcascades_cuda/haarcascade_frontalface_alt.xml";
    String eyes_cascade_name = "/home/ieg/Belgeler/openCV/opencv/data/haarcascades_cuda/haarcascade_eye_tree_eyeglasses.xml";

    CascadeClassifier face_cascade;
    CascadeClassifier eyes_cascade;
    void detectAndDisplay(Mat frame);

    myopencvsources();

    int edgeMinSlider = 50;
    int edgeMaxSlider = 200;
    void imgToEdge(Mat frame);

    Mat shape_gray;
    Mat shape_bw;
    Mat shape_dst;
    vector<vector<Point> > shape_contours;
    vector<Vec4i> hierarchy;
    vector<Point> approx;

    double angle(Point pt1, Point pt2, Point pt0);
    void setLabel(Mat &im, const string label, vector<Point> &contour);
    void shapeDetect(Mat frame);

    int colorRadius = 25;
    int colorRadiusToPisc = (int) colorRadius*0.7;
    void colorDetect(Mat frame);



    /// Global variables
    Mat corner1_src, corner1_src_gray;

    int corner1_maxCorners = 23;

    void cornerDetect1(Mat frame);
    void goodFeaturesToTrack_Demo(int, void *);
};

#endif // MYOPENCVSOURCES_H
