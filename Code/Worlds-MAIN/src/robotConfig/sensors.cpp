#include "robot.h"
#include "api.h"
#include "lemlib/api.hpp"

pros::IMU Robot::Sensors::imu (6);
const lemlib::OdomSensors Robot::Sensors::odomSensors (nullptr,
                                                       nullptr,
                                                       nullptr,
                                                       nullptr,
                                                       &Robot::Sensors::imu
                                                
);