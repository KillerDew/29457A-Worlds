#include "api.h"
#include "lemlib/api.hpp"
#include "pros/rtos.hpp"
#include "usr/robot.h"

bool Robot::Catapult::IsOn = false;
float Robot::Catapult::CatapultSpeed = 0.6;
const float Robot::Catapult::ShotsPerRotation = 2;

pros::Motor CataMotor = Robot::Motors::Catapult;

void Robot::Catapult::TurnCatapultOn(){
    // Cycle catapult at cataspeed
    CataMotor.move(-127*CatapultSpeed);
    IsOn = true;
}
void Robot::Catapult::TurnCatapultOff(){
    // Stop Cycling cata
    CataMotor=0;
    IsOn = false;
}
void Robot::Catapult::ResetCatapult(){
    // Task so it does it in background
    pros::Task ([&](){
        // Sets moror to coast so RBs pull cata back to rest
        CataMotor.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
        pros::delay(750);
        // Sets motor back to hold agter 750 ms
        CataMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
    });
}
void Robot::Catapult::UseCatapultFor(int matchloads, bool async){
    IsOn = true;
    if (async){
        // If async re-call as task
        pros::Task([&](){UseCatapultFor(matchloads, false);});
        pros::delay(10);
    }else{
        // Move cata required ammount
        CataMotor.move_relative(-(360/Robot::Catapult::ShotsPerRotation)*matchloads, 127 * CatapultSpeed);
        // wait for motion to finish
        while (!CataMotor.is_stopped()){
            pros::delay(10);
        }
        IsOn = false;
    }
}
void Robot::Catapult::UseCatapultFor(double time, bool async){
    if (async){
        // If async re-call as task
        pros::Task([&](){UseCatapultFor(time, false);});
        pros::delay(10);
    }else{
        // Turn cata on, wait, turn it off
        TurnCatapultOn();
        pros::delay(time);
        TurnCatapultOff();
    }
}

