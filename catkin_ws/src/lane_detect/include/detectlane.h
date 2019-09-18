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
    pair<Point, int> calculateError(const Mat &src);
    Mat ROI(const Mat &src);
    Mat birdviewTransformation(const Mat &src);
    Mat ComputeHoughLines(const Mat &src, const Mat &ROI); 
    void detectTrafficSigns(const Mat &src, Mat &blue, int &turnFactor);
private:
    void drawLine(float slope, float y_intercept, Mat &HoughTransform);
    int minThreshold[3] = {0, 0, 180};
    int maxThreshold[3] = {179, 30, 255};
    int vote = 8;
    int cannylow = 100;
    int hough_lowerbound = 40;
    int skyline = 85;
    int turnFactor = 0;
    int oldTF = 0;

    const int offsetX = 160;
    const int offsetY = 180;
    const int max_houghThreshold = 200;
    const int max_cannylow = 100;
    const int cannyRatio = 3;
    const int kernelSize = 3;
    const float eps = 1e-7;
    const int birdwidth = 240;
    const int birdheight = 320;
    vector<Point> leftLane, rightLane;
};
#endif
