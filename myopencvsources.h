#ifndef MYOPENCVSOURCES_H
#define MYOPENCVSOURCES_H


#include "opencv2/objdetect/objdetect.hpp"
 #include "opencv2/highgui/highgui.hpp"
 #include "opencv2/imgproc/imgproc.hpp"

 #include <iostream>
 #include <stdio.h>

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
//     RNG rng(12345);

     int edgeMinSlider = 50;
     int edgeMaxSlider = 200;

    myopencvsources();
    void detectAndDisplay(Mat frame);
    void imgToEdge(Mat frame);
    void cornerHarris_demo(Mat frame);
};

#endif // MYOPENCVSOURCES_H
