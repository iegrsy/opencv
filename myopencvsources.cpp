#include "myopencvsources.h"

#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core.hpp"

#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;
using namespace cv;


myopencvsources::myopencvsources()
{

}

void myopencvsources::detectAndDisplay( Mat frame ){
    std::vector<Rect> faces;
    Mat frame_gray;

    cvtColor( frame, frame_gray, CV_BGR2GRAY );
    equalizeHist( frame_gray, frame_gray );

    //-- Detect faces
    face_cascade.detectMultiScale( frame_gray, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(30, 30) );

    for( size_t i = 0; i < faces.size(); i++ )
    {
        Point center( faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5 );
        ellipse( frame, center, Size( faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, Scalar( 255, 0, 255 ), 4, 8, 0 );

        Mat faceROI = frame_gray( faces[i] );
        std::vector<Rect> eyes;

        //-- In each face, detect eyes
        eyes_cascade.detectMultiScale( faceROI, eyes, 1.1, 2, 0 |CV_HAAR_SCALE_IMAGE, Size(30, 30) );

        for( size_t j = 0; j < eyes.size(); j++ )
        {
            Point center( faces[i].x + eyes[j].x + eyes[j].width*0.5, faces[i].y + eyes[j].y + eyes[j].height*0.5 );
            int radius = cvRound( (eyes[j].width + eyes[j].height)*0.25 );
            circle( frame, center, radius, Scalar( 255, 0, 0 ), 4, 8, 0 );
        }
    }
    //-- Show what you got
    imshow( window_name, frame );
}

void myopencvsources::imgToEdge(Mat frame){

    Mat gray, edge, draw;

    cvtColor(frame, gray, CV_BGR2GRAY);
    Canny( gray, edge, edgeMinSlider, edgeMaxSlider, 3);
    edge.convertTo(draw, CV_8U);

    imshow( window_name1, draw );
}

void myopencvsources::colorDetect(Mat frame){
    Mat gray;

    cvtColor(frame , gray , CV_BGR2GRAY);

    //    circle(gray , Point( gray.cols/2 , gray.rows/2 ) , 80 , Scalar(255,255,255), 8 , 0);
    rectangle(gray , Point(gray.cols/2 - 50,gray.rows/2 - 50) , Point(gray.cols/2 + 50,gray.rows/2 + 50),Scalar(0,0,0),8,0);

    Mat mask;
    threshold(gray, mask, 0, 255, CV_THRESH_BINARY_INV | CV_THRESH_OTSU);

    // find contours (if always so easy to segment as your image, you could just add the black/rect pixels to a vector)
    vector< vector<Point> > contours;
    vector<Vec4i> hierarchy;
    findContours(mask,contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

    /// Draw contours and find biggest contour (if there are other contours in the image, we assume the biggest one is the desired rect)
    // drawing here is only for demonstration!
    int biggestContourIdx = -1;
    float biggestContourArea = 0;
    Mat drawing = Mat::zeros( mask.size(), CV_8UC3 );
    for( int i = 0; i< contours.size(); i++ )
    {
        Scalar color = Scalar(0, 100, 0);
        drawContours( drawing, contours, i, color, 1, 8, hierarchy, 0, Point() );

        float ctArea= contourArea(contours[i]);
        if(ctArea > biggestContourArea)
        {
            biggestContourArea = ctArea;
            biggestContourIdx = i;
        }
    }

    // if no contour found
    if(biggestContourIdx < 0)
    {
        cout << "no contour found" << endl;
        return ;
    }

    // compute the rotated bounding rect of the biggest contour! (this is the part that does what you want/need)
    RotatedRect boundingBox = minAreaRect(contours[biggestContourIdx]);
    // one thing to remark: this will compute the OUTER boundary box, so maybe you have to erode/dilate if you want something between the ragged lines



    // draw the rotated rect
    Point2f corners[4];
    boundingBox.points(corners);
    line(drawing, corners[0], corners[1], Scalar(255,255,255));
    line(drawing, corners[1], corners[2], Scalar(255,255,255));
    line(drawing, corners[2], corners[3], Scalar(255,255,255));
    line(drawing, corners[3], corners[0], Scalar(255,255,255));


    imshow( window_name2, drawing );
}

void myopencvsources::shapeDetect(Mat frame){

        Mat dst;

        cvtColor(frame , dst , CV_BGR2GRAY);

        imshow(window_name3 , dst);
    }
