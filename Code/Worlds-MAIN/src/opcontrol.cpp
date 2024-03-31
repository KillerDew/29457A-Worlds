#include "display/lv_misc/lv_color.h"
#include "lemlib/chassis/chassis.hpp"
#include "pros/misc.h"
#include "pros/misc.hpp"
#include "pros/motors.h"
#include "pros/optical.hpp"
#include "pros/rtos.hpp"
#include "robot.h"
#include "api.h"
#include "lemlib/api.hpp"
#include "Inputs.h"


const DriverType Robot::OpControl::driverType = Curvature;

const float Robot::OpControl::dt = 10;

const pros::Controller Robot::OpControl::Master (pros::E_CONTROLLER_MASTER);

bool Robot::OpControl::breakLoop = false;

const float Robot::OpControl::ThrottleDeadzone = 127*0.05;
const float Robot::OpControl::TurnDeadzone = 127*0.05;
bool Robot::OpControl::Idle = true;
const float Robot::OpControl::HOLDThreshold = 500;

float* Robot::OpControl::ProcessMovementInputs(float a, float b){
    if (a > -ThrottleDeadzone && a < ThrottleDeadzone){
        a = 0;
    }
    if (b > -TurnDeadzone && b < TurnDeadzone){
        b = 0;
    }
    if (a==0 && b==0)
        Idle = true;
    else
     Idle = false;
    float output[2]{a, b};
    return output;
}
void Robot::OpControl::DrivetrainMovement(){
    float a;
        float b;
        float* inputs;
        switch (driverType) {
            case 0: // Arcade
                a = ControllerInputs::Analogue::LeftY;
                b = ControllerInputs::Analogue::LeftX;
                inputs = ProcessMovementInputs(a, b);
                chassis.arcade(inputs[0], inputs[1]);
                break;
            case 1: // Split Arcade
                a = ControllerInputs::Analogue::LeftY;
                b = ControllerInputs::Analogue::RightX;
                inputs = ProcessMovementInputs(a, b);
                chassis.arcade(inputs[0], inputs[1]);
                break;
            case 2: // Curvature
                a = ControllerInputs::Analogue::LeftY;
                b = ControllerInputs::Analogue::LeftX;
                inputs = ProcessMovementInputs(a, b);
                chassis.curvature(inputs[0], inputs[1]);
                break;
            case 3: // Split Curvature
                a = ControllerInputs::Analogue::LeftY;
                b = ControllerInputs::Analogue::RightX;
                inputs = ProcessMovementInputs(a, b);
                chassis.curvature(inputs[0], inputs[1]);
                break;
            case 4:
                a = ControllerInputs::Analogue::LeftY;
                b = ControllerInputs::Analogue::RightY;
                inputs = ProcessMovementInputs(a, b);
                chassis.tank(inputs[0], inputs[1]);
                break;
        }
}
void Robot::OpControl::DriverControlLoop(){

    Timer Idletimer;
    Timer BalanceTimer;
    BalanceTimer.TurnToAfter(60*1000, &Robot::BalanceMech::CanDrop, true);

    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_COAST);

    while (!breakLoop){

        if (Idle && Idletimer.GetElapsed() >= HOLDThreshold){
            chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);
        }else if (!Idle){
            Idletimer.Reset();
            chassis.setBrakeMode(pros::E_MOTOR_BRAKE_COAST);
        }
        ControllerInputs::GetInputs(Master);
        DrivetrainMovement();

        if (ControllerInputs::Digital::New::B){
            Robot::BalanceMech::DropBalance(); // Only Works in last 30 secs
        }
        if (ControllerInputs::Digital::New::R1){
            Robot::Wings::ToggleWings();
        }

        if (ControllerInputs::Digital::R2){
            Robot::Intake::Intake_();
        }else if (ControllerInputs::Digital::L2){
            Robot::Intake::Outtake();
        }else {
            Robot::Intake::Stop();
        }
        
        if (ControllerInputs::Digital::X){
            Robot::Catapult::TurnCatapultOn();
        }else {
            Robot::Catapult::TurnCatapultOff();
        }
        pros::delay(dt);
    }
}

