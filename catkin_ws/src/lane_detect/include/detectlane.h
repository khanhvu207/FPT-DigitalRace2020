#ifndef DETECTLANE_H
#define DETECTLANE_H

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>

#include <ros/ros.h>
#include <vector>
#include <math.h>
#include <algorithm>
#include <iostream>

using namespace std;
using namespace cv;

class DetectLane
{
public:
    DetectLane();
    ~DetectLane();
    Point calculateError(const Mat &src);
private:
    void drawLine(float slope, float y_intercept, Mat &HoughTransform);
    int cannylow = 80;
    int hough_lowerbound = 60;
    const int max_houghThreshold = 200;
    const int max_cannylow = 100;
    const int cannyRatio = 3;
    const int kernelSize = 3;
    const float eps = 1e-7;
    vector<Point> leftLane, rightLane;
};
#endif
