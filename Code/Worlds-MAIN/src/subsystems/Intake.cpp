#include "api.h"
#include "lemlib/api.hpp"
#include "usr/robot.h"
#include <cmath>

int Robot::Intake::Direction = 0;

pros::MotorGroup* intake = &Robot::Motors::Intake;
void Robot::Intake::Outtake(){
    intake->move(-127);
    Direction = -1;
}
void Robot::Intake::Intake_(){
    intake->move(127);
    Direction=1;
}
void Robot::Intake::Stop(){
    intake->set_brake_modes(pros::E_MOTOR_BRAKE_HOLD);
    intake->brake();
    Direction=0;
}

void Robot::Intake::IntakeFor(float time, bool async){
    if (async){
        pros::Task([&](){Robot::Intake::IntakeFor(time, false);});
        pros::delay(5);// Wait for task to start
    }      
    else{
        Robot::Intake::Intake_();
        pros::delay(time);
        Robot::Intake::Stop();
    }
}
void Robot::Intake::OuttakeFor(float time, bool async){
    if (async){
        pros::Task([&](){Robot::Intake::OuttakeFor(time, false);});
        pros::delay(5);
    }
    else{
        Robot::Intake::Outtake();
        pros::delay(time);
        Robot::Intake::Stop();
    }
}
void Robot::Intake::IntakeTriball(float dist, bool async){
    if (async){
        pros::Task([&](){Robot::Intake::IntakeTriball(dist, false);});
        pros::delay(5);
    }else{
        Robot::Intake::Intake_();
        lemlib::Pose pos = chassis.getPose(true);
        float x = pos.x + dist*cos(pos.theta);
        float y = pos.y + dist*sin(pos.theta);
        Robot::chassis.moveToPose(x, y, pos.theta, 250);
        chassis.waitUntilDone();
        Robot::Intake::Stop();
    }
}