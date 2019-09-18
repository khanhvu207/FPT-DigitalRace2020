#include "carcontrol.h"

CarControl::CarControl()
{
    carPos.x = 160;
    carPos.y = 180;
    //cvCreateTrackbar("kP", "Threshold", &kP, 50);
    //cvCreateTrackbar("kD", "Threshold", &kD, 50);
    steer_publisher = node_obj1.advertise<std_msgs::Float32>("Team1_steerAngle",10);
    speed_publisher = node_obj2.advertise<std_msgs::Float32>("Team1_speed",10);
}

CarControl::~CarControl() {}

float CarControl::errorAngle(const Point &dst)
{
    float X = dst.x - carPos.x;
    float Y = dst.y;
    float angle = atan2(Y, X) * 180.0 / CV_PI - 90.0;
    return angle;
}

void CarControl::driverCar(const pair<Point, int> &cur, float velocity)
{
    std_msgs::Float32 angle;
    std_msgs::Float32 speed;
    carPos.x = 160;   
    carPos.x += cur.second * auxTurn;
    float error = -errorAngle(cur.first);
    
    //PID controller
    t_kP = error;
    t_kI += error;
    t_kD = error - preError;
    angle.data = kP * t_kP + kI * t_kI + kD * t_kD;
    speed.data = fabs(error) < 1 ? maxVelocity : (velocity - fabs(error) * 0.5);
    preError = error;
    steer_publisher.publish(angle);
    speed_publisher.publish(speed);    
} 
