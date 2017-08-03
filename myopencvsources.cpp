#include "myopencvsources.h"

#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core.hpp"

#include <iostream>
#include <stdio.h>
#include <vector>

#include <QDebug>

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

    Mat color= frame.clone();

    circle(color , Point(color.cols/2,color.rows/2) , colorRadius , Scalar(255,0,0) , 1 , 8 , 0);

    int colorAvgR = 0;
    int colorAvgG = 0;
    int colorAvgB = 0;
    Vec3b temp;
    int count=0;
    for(int j = (color.rows/2-colorRadiusToPisc) ; j<(color.cols/2+colorRadiusToPisc) ; j++){
        for(int i = (color.cols/2-colorRadiusToPisc) ; i < (color.cols/2+colorRadiusToPisc) ; i++){
            temp = color.at<Vec3b>(j,i);

            colorAvgB += (int) temp.val[0];
            colorAvgG += (int) temp.val[1];
            colorAvgR += (int) temp.val[2];
            count++;
        }
    }
    circle(color , Point(color.cols-50,color.rows-50) , 35 ,
           Scalar(colorAvgB / (count) , colorAvgG / (count) , colorAvgR / (count) ),
           CV_FILLED , 8 , 0);

    imshow( window_name2, color );
}

void myopencvsources::shapeDetect(Mat frame){
    // Convert to grayscale
    cvtColor(frame, shape_gray, CV_BGR2GRAY);

    // Use Canny instead of threshold to catch squares with gradient shading
    blur( shape_gray, shape_bw, Size(3,3) );
    Canny(shape_gray, shape_bw, 80, 240, 3);
    //    imshow("shape_bw", shape_bw);
    //bitwise_not(shape_bw, shape_bw);

    // Find shape_contours
    findContours(shape_bw.clone(), shape_contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

    frame.copyTo(shape_dst);

    for (int i = 0; i < shape_contours.size(); i++)
    {
        // Approximate contour with accuracy proportional
        // to the contour perimeter
        approxPolyDP(Mat(shape_contours[i]), approx, arcLength(Mat(shape_contours[i]), true)*0.02, true);

        // Skip small or non-convex objects
        if (fabs(contourArea(shape_contours[i])) < 200 || !isContourConvex(approx))
            continue;

        if (approx.size() == 3)
        {
            setLabel(shape_dst, "TRI", shape_contours[i]);    // Triangles
            drawContours(shape_dst, shape_contours, i, Scalar(0, 255, 255), 5);
        }
        else if (approx.size() >= 4 && approx.size() <= 6)
        {
            // Number of vertices of polygonal curve
            int vtc = approx.size();

            // Get the cosines of all corners
            vector<double> cos;
            for (int j = 2; j < vtc+1; j++)
                cos.push_back(angle(approx[j%vtc], approx[j-2], approx[j-1]));

            // Sort ascending the cosine values
            sort(cos.begin(), cos.end());

            // Get the lowest and the highest cosine
            double mincos = cos.front();
            double maxcos = cos.back();

            // Use the degrees obtained above and the number of vertices
            // to determine the shape of the contour
            if (vtc == 4 ){
                setLabel(shape_dst, "RECT", shape_contours[i]);
                drawContours(shape_dst, shape_contours, i, Scalar(0, 0, 255), 5);
            }
            else if (vtc == 5 ){
                setLabel(shape_dst, "PENTA", shape_contours[i]);
                drawContours(shape_dst, shape_contours, i, Scalar(0, 255, 0), 5);
            }
            else if (vtc == 6 ){
                setLabel(shape_dst, "HEXA", shape_contours[i]);
                drawContours(shape_dst, shape_contours, i, Scalar(255, 0, 255), 5);
            }
        }
        else
        {
            // Detect and label circles
            double area = contourArea(shape_contours[i]);
            Rect r = boundingRect(shape_contours[i]);
            int radius = r.width / 2;

            if (abs(1 - ((double)r.width / r.height)) <= 0.2 &&
                    abs(1 - (area / (CV_PI * (radius*radius)))) <= 0.2){
                setLabel(shape_dst, "CIR", shape_contours[i]);
                drawContours(shape_dst, shape_contours, i, Scalar(255, 0, 0), 5);
            }
        }
    }

    imshow(window_name3 , shape_dst);
}

double myopencvsources::angle(Point pt1, Point pt2, Point pt0)
{
    double dx1 = pt1.x - pt0.x;
    double dy1 = pt1.y - pt0.y;
    double dx2 = pt2.x - pt0.x;
    double dy2 = pt2.y - pt0.y;
    return (dx1*dx2 + dy1*dy2)/sqrt((dx1*dx1 + dy1*dy1)*(dx2*dx2 + dy2*dy2) + 1e-10);
}

void myopencvsources::setLabel(Mat& im, const string label, vector<Point>& contour)
{
    int fontface = FONT_HERSHEY_SIMPLEX;
    double scale = 0.4;
    int thickness = 1;
    int baseline = 0;

    Size text = getTextSize(label, fontface, scale, thickness, &baseline);
    Rect r = boundingRect(contour);

    Point pt(r.x + ((r.width - text.width) / 2), r.y + ((r.height + text.height) / 2));
    rectangle(im, pt + Point(0, baseline), pt + Point(text.width, -text.height), CV_RGB(255,255,255), CV_FILLED);
    putText(im, label, pt, fontface, scale, CV_RGB(0,0,0), thickness, 8);
}

void myopencvsources::cornerDetect1(Mat frame){

      corner1_src = frame;
      cvtColor( corner1_src, corner1_src_gray, CV_BGR2GRAY );

      goodFeaturesToTrack_Demo( 0, 0 );
}

void myopencvsources::goodFeaturesToTrack_Demo( int, void* )
{
  if( corner1_maxCorners < 1 ) { corner1_maxCorners = 1; }

  /// Parameters for Shi-Tomasi algorithm
  vector<Point2f> corners;
  double qualityLevel = 0.01;
  double minDistance = 10;
  int blockSize = 3;
  bool useHarrisDetector = false;
  double k = 0.04;

  /// Copy the source image
  Mat copy;
  copy = corner1_src.clone();

  /// Apply corner detection
  goodFeaturesToTrack( corner1_src_gray , corners , corner1_maxCorners , qualityLevel , minDistance ,
                       Mat() , blockSize , useHarrisDetector , k );

  int r = 4;
  for( int i = 0; i < corners.size(); i++ )
     { circle( copy, corners[i], r, Scalar(255,0,0), -1, 8, 0 ); }

  putText(copy , QString::number(corners.size()).toStdString(),
          Point(20,30) , cv::FONT_HERSHEY_SIMPLEX , 1 ,
          Scalar(255,250,0) , 2 , cv::LINE_AA );

  imshow( window_name4, copy );
}
