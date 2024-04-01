#include "lemlib/api.hpp"
#include "robot.h"

lemlib::Chassis Robot::chassis (
    Robot::Motors::drivetrain,
    Robot::Tunables::linearController,
    Robot::Tunables::angularController,
    Robot::Sensors::odomSensors
);