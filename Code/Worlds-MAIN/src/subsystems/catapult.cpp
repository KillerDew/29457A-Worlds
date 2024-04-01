#include "api.h"
#include "lemlib/api.hpp"
#include "robot.h"

bool Robot::Catapult::IsOn = false;
float Robot::Catapult::CatapultSpeed = 0.4;
const float Robot::Catapult::ShotsPerRotation = 2;

pros::Motor CataMotor = Robot::Motors::Catapult;

void Robot::Catapult::TurnCatapultOn(){
    CataMotor.move(-127*Robot::Catapult::CatapultSpeed);
    IsOn = true;
}
void Robot::Catapult::TurnCatapultOff(){
    CataMotor=0;
    IsOn = false;
}
void Robot::Catapult::ResetCatapult(){
    pros::Task ([&](){
        CataMotor.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
        pros::delay(750);
        CataMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
    });
}
void Robot::Catapult::UseCatapultFor(int matchloads, bool async){
    IsOn = true;
    if (async){
        pros::Task ([&](){
            CataMotor.move_relative(-(360/Robot::Catapult::ShotsPerRotation)*matchloads, 127 * CatapultSpeed);
            while (!CataMotor.is_stopped()){
                pros::delay(10);
            }
            IsOn = false;
        });
    }else{
        CataMotor.move_relative(-(360/Robot::Catapult::ShotsPerRotation)*matchloads, 127 * CatapultSpeed);
        while (!CataMotor.is_stopped()){
            pros::delay(10);
        }
        IsOn = false;
    }
}
void Robot::Catapult::UseCatapultFor(double time, bool async){
    if (async){
        pros::Task ([&](){
            TurnCatapultOn();
            pros::delay(time);
            TurnCatapultOff();
        });
    }else{
        TurnCatapultOn();
        pros::delay(time);
        TurnCatapultOff();
    }
}

