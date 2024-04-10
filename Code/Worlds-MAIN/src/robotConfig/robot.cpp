#include "lemlib/api.hpp"
#include "usr/robot.h"

// Decleration of chassis
lemlib::Chassis Robot::chassis (
    Robot::Motors::drivetrain,
    Robot::Tunables::linearController,
    Robot::Tunables::angularController,
    Robot::Sensors::odomSensors
);
