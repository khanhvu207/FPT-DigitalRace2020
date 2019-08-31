#ifndef CARCONTROL_H
#define CARCONTROL_H
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>

#include <ros/ros.h>
#include "std_msgs/Float32.h"

#include <vector>
#include <math.h>
#include <iostream>

#include "detectlane.h"

using namespace std;
using namespace cv;

class CarControl 
{
public:
    CarControl();
    ~CarControl();
    void driverCar(const Point &cur, float velocity);

private:
    ros::NodeHandle node_obj1;
    ros::NodeHandle node_obj2;
    ros::Publisher steer_publisher;
    ros::Publisher speed_publisher;
    Point carPos;
    float errorAngle(const Point &dst);
    float laneWidth = 40;
    float minVelocity = 10;
    float maxVelocity = 60;
    float preError;
    float kP = 0.15;
    float kI = 0.00031;
    float kD = 1.3;
    float t_kP = 0.0;
    float t_kI = 0.0;
    float t_kD = 0.0;
};
#endif
