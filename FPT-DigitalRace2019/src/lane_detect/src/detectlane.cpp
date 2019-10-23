#include "detectlane.h"

DetectLane::DetectLane() {
    //cvCreateTrackbar("Hough", "Threshold", &hough_lowerbound, max_houghThreshold);
}

DetectLane::~DetectLane(){} 

Mat preZoom(240, 320, CV_8UC1);

void DetectLane::drawLine(float slope, float y_intercept, Mat &windows) {
    float y0 = 240.0;
    float y1 = 1.0;
    float x0 = (y0 - y_intercept) / slope;
    float x1 = (y1 - y_intercept) / slope;
    line(windows, Point(x0, y0), Point(x1, y1), Scalar(0, 255, 0), 2, LINE_AA);
}

Mat DetectLane::ROI(const Mat &src) {
    //Crop region of interest (ROI)
    int W = src.size().width;
    int H = src.size().height;
    Mat RegionOfInterest;
    Mat mask = Mat::zeros(src.size(), CV_8UC1);

    vector<Point> vertices;
    vertices.push_back(Point(0, skyline));
    vertices.push_back(Point(W, skyline));
    vertices.push_back(Point(W, H));
    vertices.push_back(Point(0, H));
    
    fillConvexPoly(mask, vertices, Scalar(255, 255, 255), 8, 0);
    bitwise_and(src, mask, RegionOfInterest);
    
    //imshow("RegionOfInterest", RegionOfInterest);
    return RegionOfInterest;
}

Mat DetectLane::birdviewTransformation(const Mat &src) {
    int W = src.size().width;
    int H = src.size().height;

    Point2f srcVertices[4];
    srcVertices[0] = Point(0, skyline);
    srcVertices[1] = Point(W, skyline);
    srcVertices[2] = Point(W, H);
    srcVertices[3] = Point(0, H);

    Point2f dstVertices[4];
    dstVertices[0] = Point(0, 0);
    dstVertices[1] = Point(birdwidth, 0);
    dstVertices[2] = Point(birdwidth - 100, birdheight);
    dstVertices[3] = Point(100, birdheight);

    Mat M = getPerspectiveTransform(srcVertices, dstVertices);
    Mat birdview(birdwidth, birdheight, CV_8UC3);
    warpPerspective(src, birdview, M, birdview.size(), INTER_LINEAR, BORDER_CONSTANT);

    imshow("birdview", birdview);
    return birdview;
}

void DetectLane::detectTrafficSigns(const Mat &src, Mat &blue, int &turnFactor) {
    Mat canvas = Mat::zeros(src.size(), CV_8UC3);

    vector<vector<Point>> contours;
    findContours(blue, contours, RETR_TREE, CHAIN_APPROX_SIMPLE);

    if (!contours.empty()) {
        
        vector<vector<Point>> contoursPoly((int)contours.size());
        vector<Rect> boundRect((int)contours.size());

        for (int i = 0; i < (int)contours.size(); ++i) {
            approxPolyDP(contours[i], contoursPoly[i], 3, true);
            boundRect[i] = boundingRect(contoursPoly[i]);    
        }

        int maxArea = 0, bestRect;
        for (int i = 0; i < (int)boundRect.size(); ++i) {
            int boundRect_W = abs(boundRect[i].tl().x - boundRect[i].br().x);
            int boundRect_H = abs(boundRect[i].tl().y - boundRect[i].br().y);
            if (boundRect_W * boundRect_H > maxArea) {
                maxArea = boundRect_W * boundRect_H;
                bestRect = i;
            }
        }

        if (maxArea < 125) goto skip;

        Point topLeft = boundRect[bestRect].tl();
        Point bottomRight = boundRect[bestRect].br();
        rectangle(canvas, topLeft, bottomRight, Scalar(0, 0, 255), 2, 8, 0);

        int rectW = abs(topLeft.x - bottomRight.x) * 4;
        int rectH = abs(topLeft.y - bottomRight.y) * 4;
        Mat zoom(rectW, rectH, CV_8UC1);
        Point2f boundingBox[4], zoomBox[4];
        
        boundingBox[0] = topLeft;
        boundingBox[1] = Point(bottomRight.x, topLeft.y);
        boundingBox[2] = bottomRight;
        boundingBox[3] = Point(topLeft.x, bottomRight.y);

        zoomBox[0] = Point(0, 0);
        zoomBox[1] = Point(rectW, 0);
        zoomBox[2] = Point(rectW, rectH);
        zoomBox[3] = Point(0, rectH);

        Mat M = getPerspectiveTransform(boundingBox, zoomBox);
        warpPerspective(blue, zoom, M, zoom.size(), INTER_LINEAR, BORDER_CONSTANT);

        int cntLeftOnes = 0, cntRightOnes = 0;
        for (int i = 0; i < rectW; ++i)
            for (int j = 0; j < rectH; ++j) 
                if ((int)zoom.at<uchar>(i, j) == 255) {
                    if (i < rectW / 2) ++cntLeftOnes;
                        else ++cntRightOnes;
                }

        cntLeftOnes = cntLeftOnes * cntLeftOnes;
        cntRightOnes = cntRightOnes * cntRightOnes;
        turnFactor = cntLeftOnes > cntRightOnes ? 1 : -1;   
    }

    skip: 
    addWeighted(src, 0.5, canvas, 1, 1, canvas);
    imshow("Blue", blue);
    imshow("SignsDetector", canvas);
}

void DetectLane::showShadow(const Mat &src)
{
    Mat shadowMask, shadow, imgHSV, shadowHSV, laneShadow;
    cvtColor(src, imgHSV, COLOR_BGR2HSV);
    inRange(imgHSV, Scalar(minShadowTh[0], minShadowTh[1], minShadowTh[2]), Scalar(maxShadowTh[0], maxShadowTh[1], maxShadowTh[2]),  shadowMask);
    src.copyTo(shadow, shadowMask);
    cvtColor(shadow, shadowHSV, COLOR_BGR2HSV);
    //inRange(shadowHSV, Scalar(minLaneInShadow[0], minLaneInShadow[1], minLaneInShadow[2]), Scalar(maxLaneInShadow[0], maxLaneInShadow[1], maxLaneInShadow[2]), laneShadow);
    
    imshow("shadow", shadow);
}

pair<Point, int> DetectLane::calculateError(const Mat &src) {
    turnFactor = 0;
    Mat hsv, binary, RegionOfInterest, birdview, trafficSigns, blue;

    //Shadow handler
    showShadow(src);

    cvtColor(src, hsv, COLOR_BGR2HSV);
    inRange(hsv, Scalar(40, 180, 180), Scalar(240, 255, 255), blue);
    inRange(hsv, Scalar(minThreshold[0], minThreshold[1], minThreshold[2]), Scalar(maxThreshold[0], maxThreshold[1], maxThreshold[2]), binary);
    imshow("Blue", blue);

    RegionOfInterest = ROI(binary);
    //imshow("ROI", RegionOfInterest);

    //Bird's view transformation
    birdview = birdviewTransformation(binary);

    //Apply Hough transformation
    vector<Vec4f> lines;
    HoughLinesP(RegionOfInterest, lines, 1, CV_PI / 180, hough_lowerbound, 10, 5);
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

    //Detect signs
    detectTrafficSigns(src, blue, turnFactor);
    if (turnFactor != 0) oldTF = turnFactor;

    //Get current position base on left & right edges
    float midY = offsetY;
    float midX = offsetX;
    if (cntL == 0.0 && cntR > 0) {
        midX = (midY - rightYintercept_average) / rightSlope_average;
    } else 
    if (cntL > 0 && cntR == 0.0) {
        midX = (midY - leftYintercept_average) / leftSlope_average;
    } else
        midX = (((midY - leftYintercept_average) / leftSlope_average) + ((midY - rightYintercept_average) / rightSlope_average)) / 2.0;
    
    if (cntL == 0 && cntR == 0) {
        turnFactor = oldTF;
        midX = turnFactor == 1 ? (offsetX + 120) : (offsetX - 120);
    }
    else if (cntL == 0 && !turnFactor) 
        midX = midX < offsetX ? (midX + 120) : (offsetX - 40);
    else if (cntR == 0 && !turnFactor) 
        midX = midX > offsetX ? (midX - 120) : (offsetX + 40);
    
    Point cur = Point(midX, midY);
    circle(HoughTransform, Point(offsetX + turnFactor * 30, offsetY), 3, Scalar(0, 255, 0), -1);
    circle(HoughTransform, cur, 3, Scalar(255, 0, 0), -1);
    
    imshow("HoughTransform", HoughTransform);
    return pair<Point, int>(Point(midX, midY), turnFactor);
}

