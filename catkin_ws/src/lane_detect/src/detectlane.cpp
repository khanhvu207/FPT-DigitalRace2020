#include "detectlane.h"

DetectLane::DetectLane() {
    cvCreateTrackbar("CannyLow", "Threshold", &cannylow, max_cannylow);
    cvCreateTrackbar("Hough", "Threshold", &hough_lowerbound, max_houghThreshold);
}

DetectLane::~DetectLane(){}

void DetectLane::drawLine(float slope, float y_intercept, Mat &HoughTransform) {
    float y0 = 240.0;
    float y1 = y0 * 2 / 5;
    float x0 = (y0 - y_intercept) / slope;
    float x1 = (y1 - y_intercept) / slope;
    line(HoughTransform, Point(x0, y0), Point(x1, y1), Scalar(0, 255, 0), 2, LINE_AA);
}

Point DetectLane::calculateError(const Mat &src)
{
    Mat gray, blur, canny, RegionOfInterest;
    
    //Grayscale imageframes
    cvtColor(src, gray, COLOR_BGR2GRAY);
    imshow("Grayscale", gray);
    
    //Apply Guassian Blur & Canny Edge detector 
    GaussianBlur(gray, blur, Size(kernelSize, kernelSize), 0, 0);
    Canny(blur, canny, cannylow, cannylow * cannyRatio, kernelSize);
    imshow("Canny EdgesDetector", canny);

    //Crop region of interest (ROI)
    Mat mask = Mat::zeros(src.size(), CV_8UC1);
    Size S = src.size();
    vector<Point> vertices;
    vertices.push_back(Point(90, 100));
    vertices.push_back(Point(220, 100));
    vertices.push_back(Point(350, 240));
    vertices.push_back(Point(-10, 180));
    fillConvexPoly(mask, vertices, Scalar(255, 255, 255), 8, 0);
    bitwise_and(canny, mask, RegionOfInterest);
    imshow("RegionOfInterest", RegionOfInterest);

    //Apply Hough transformation
    vector<Vec4f> lines;
    HoughLinesP(RegionOfInterest, lines, 1, CV_PI / 180, hough_lowerbound, 40, 5);
    Mat HoughTransform = Mat::zeros(src.size(), CV_8UC3);
    float cntL = 0.0, cntR = 0.0;
    float leftSlope_average = 0.0;
    float rightSlope_average = 0.0;
    float leftYintercept_average = 0.0;
    float rightYintercept_average = 0.0;
    for (int i = 0; i < (int)lines.size(); ++i) {
        Vec4f t = lines[i]; //x0, y0, x1, y1
        float slope = (t[1] - t[3]) / (t[0] - t[2]);
        float Yintercept = t[1] - slope * t[0];
        if (slope < 0.0) 
            leftSlope_average += slope, leftYintercept_average += Yintercept, cntL += 1.0;
        else
            rightSlope_average += slope, rightYintercept_average += Yintercept, cntR += 1.0;
    }
    if (cntL > 0) {
        leftSlope_average /= cntL;
        leftYintercept_average /= cntL;
        drawLine(leftSlope_average, leftYintercept_average, HoughTransform);
    }
    if (cntR > 0) {
        rightSlope_average /= cntR;
        rightYintercept_average /= cntR;
        drawLine(rightSlope_average, rightYintercept_average, HoughTransform);
    }
    addWeighted(src, 0.5, HoughTransform, 1, 1, HoughTransform);
    imshow("HoughTransform", HoughTransform);

    //Get current position base on left & right edges
    float midY = 200;
    float midX;
    if (cntL == 0.0 && cntR > 0) {
        midX = (midY - rightYintercept_average) / rightSlope_average;
        midX -= 20;
    } else 
    if (cntL > 0 && cntR == 0.0) {
        midX = (midY - leftYintercept_average) / leftSlope_average;
        midX += 20;
    } else
        midX = (((midY - leftYintercept_average) / leftSlope_average) + ((midY - rightYintercept_average) / rightSlope_average)) / 2.0;
    Point cur = Point(midX, midY);
    return Point(midX, midY);
}

