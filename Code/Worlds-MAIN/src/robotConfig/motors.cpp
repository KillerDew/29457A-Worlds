#include "usr/robot.h"
#include "api.h"
#include "lemlib/api.hpp"

using namespace pros;

Motor Robot::Motors::Catapult (6, E_MOTOR_GEAR_100);
MotorGroup Robot::Motors::Intake ({11, -1});

pros::Motor lF(-17, pros::E_MOTOR_GEARSET_06); // left front motor. port 17, reversed
pros::Motor lM(-18, pros::E_MOTOR_GEARSET_06); // left middle motor. port 18, reversed
pros::Motor lB(-19, pros::E_MOTOR_GEARSET_06); // left back motor. port 19, reversed
pros::Motor rF(7, pros::E_MOTOR_GEARSET_06); // right front motor. port 7
pros::Motor rM(12, pros::E_MOTOR_GEARSET_06); // right middle motor. port 12
pros::Motor rB(9, pros::E_MOTOR_GEARSET_06); // right back motor. port 9

// motor groups
MotorGroup Robot::Motors::leftDrive({lF, lM, lB}); // left motor group
MotorGroup Robot::Motors::rightDrive({rF, rM, rB}); // right motor group
lemlib::Drivetrain Robot::Motors::drivetrain (&Robot::Motors::leftDrive,
                                            &Robot::Motors::rightDrive,
                                            Robot::Dimensions::TrackWidth,
                                            Robot::Dimensions::WheelDiam,
                                            Robot::Dimensions::WheelRPM,
                                            Robot::Tunables::ChasePower);
