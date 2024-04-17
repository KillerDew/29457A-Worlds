#include "pros/motors.h"
#include "usr/robot.h"
#include "api.h"
#include "lemlib/api.hpp"

using namespace pros;

Motor Robot::Motors::Catapult (11, E_MOTOR_GEAR_100); // Catapult: Red cartridge, port 11
Motor Robot::Motors::Intake (9, E_MOTOR_GEARSET_06); // Intake on Port 9


// * LEFT MOTORS ARE REVERSED
pros::Motor lF(-10, pros::E_MOTOR_GEARSET_06); // Blue catridge, port 10
pros::Motor lM(-8, pros::E_MOTOR_GEARSET_06); // Blue catridge, port 8
pros::Motor lB(-7, pros::E_MOTOR_GEARSET_06); // Blue catridge, port 7
pros::Motor rF(20, pros::E_MOTOR_GEARSET_06); // Blue catridge, port 20
pros::Motor rM(18, pros::E_MOTOR_GEARSET_06); // Blue catridge, port 18
pros::Motor rB(17, pros::E_MOTOR_GEARSET_06); // Blue catridge, port 17

// motor groups
MotorGroup Robot::Motors::leftDrive({lF, lM, lB}); // left drive motor group
MotorGroup Robot::Motors::rightDrive({rF, rM, rB}); // right drive motor group

// Decleration of drivetrain
lemlib::Drivetrain Robot::Motors::drivetrain (&Robot::Motors::leftDrive,
                                            &Robot::Motors::rightDrive,
                                            Robot::Dimensions::TrackWidth,
                                            Robot::Dimensions::WheelDiam,
                                            Robot::Dimensions::WheelRPM,
                                            Robot::Tunables::ChasePower);
