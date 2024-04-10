#include "api.h"
#include "lemlib/api.hpp"
#include "usr/robot.h"
#include <cmath>

int Robot::Intake::Direction = 0;

pros::MotorGroup* intake = &Robot::Motors::Intake;
void Robot::Intake::Outtake(){
    // Set Motors to reverse and set direction to -1
    intake->move(-127);
    Direction = -1;
}
void Robot::Intake::Intake_(){
    // Set Motors to forwards and set direction to 1
    intake->move(127);
    Direction=1;
}
void Robot::Intake::Stop(){
    // Make sure brake mode is HOLD
    intake->set_brake_modes(pros::E_MOTOR_BRAKE_HOLD);
    // stop intake
    intake->brake();
    // Set Direction to 0 (stopped)
    Direction=0;
}

void Robot::Intake::IntakeFor(float time, bool async){
    if (async){
        // If async re-call as task
        pros::Task([&](){Robot::Intake::IntakeFor(time, false);});
        pros::delay(10);// Wait for task to start
    }      
    else{
        // Intake, Wait for time, Stop
        Robot::Intake::Intake_();
        pros::delay(time);
        Robot::Intake::Stop();
    }
}
void Robot::Intake::OuttakeFor(float time, bool async){
    if (async){
        // If async re-call as task
        pros::Task([&](){Robot::Intake::OuttakeFor(time, false);});
        pros::delay(10); // Wait for task to start
    }
    else{
        // Outtake, Wait for time, Stop
        Robot::Intake::Outtake();
        pros::delay(time);
        Robot::Intake::Stop();
    }
}
void Robot::Intake::IntakeTriball(float dist, bool async){
    if (async){
        // If async re-call as task
        pros::Task([&](){Robot::Intake::IntakeTriball(dist, false);});
        pros::delay(10); // Wait for task to start
    }else{
        // Start Intaking
        Robot::Intake::Intake_();

        /*
        * Works out Target Pos:
        * Forward Dir = (cos(-theta+(pi/2)), sin(-theta+(pi/2)))
        * Target Pos = CurrentPos + dist*ForwardDir
        */
        lemlib::Pose pos = chassis.getPose(true);
        float x = pos.x + dist*cos(-pos.theta+(M_PI/2));
        float y = pos.y + dist*sin(-pos.theta+(M_PI/2));
        // Moves to target
        Robot::chassis.moveToPose(x, y, pos.theta, 250);

        // Waits till done then stops intake
        chassis.waitUntilDone();
        Robot::Intake::Stop();
    }
}