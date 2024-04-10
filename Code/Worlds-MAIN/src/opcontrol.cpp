#include "usr/robot.h"
#include "api.h"
#include "lemlib/api.hpp"
#include "usr/Inputs.h"
#pragma clang diagnostic ignored "-Wreturn-stack-address"

// Driver Type init
const DriverType Robot::OpControl::driverType = Curvature;

// Driver loop dt init
const float Robot::OpControl::dt = 10;

// Init Controller
const pros::Controller Robot::OpControl::Master (pros::E_CONTROLLER_MASTER);

// Wether to break the loop
bool Robot::OpControl::breakLoop = false;

// Deadzone for throttle and turn
const float Robot::OpControl::ThrottleDeadzone = 127*0.05;
const float Robot::OpControl::TurnDeadzone = 127*0.05;

// Wether the drivetrain is Idle
bool Robot::OpControl::Idle = true;
// Time after idle to switch to HOLD
const float Robot::OpControl::HOLDThreshold = 500;

// Applies deadzones
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
// Processes drivetrain inputs
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

// Main driver control loop
void Robot::OpControl::DriverControlLoop(){

    // Init timers
    Timer Idletimer;
    Timer BalanceTimer;
    // Only allow Balance mech drop after 60 secs
    BalanceTimer.TurnToAfter(60*1000, &Robot::BalanceMech::CanDrop, true);

    // Set brake mode as coas
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_COAST);

    // Main Loop
    while (!breakLoop){

        // Handle HOLD if idle behaviour
        if (Idle && Idletimer.GetElapsed() >= HOLDThreshold){
            chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);
        }else if (!Idle){
            Idletimer.Reset();
            chassis.setBrakeMode(pros::E_MOTOR_BRAKE_COAST);
        }
        // Get ALL inputs and store in 'ControllerInputs' class
        ControllerInputs::GetInputs(Master);

        // Handle drivetrain movements
        DrivetrainMovement();

        // Balance mech activation (can drop test performed in function)
        if (ControllerInputs::Digital::New::B){
            Robot::BalanceMech::DropBalance(); // Only Works in last 30 secs
        }
        // Wings buttons
        if (ControllerInputs::Digital::New::R1){
            Robot::Wings::ToggleWings();
        }

        // Intake and outtaking buttons
        if (ControllerInputs::Digital::R2){
            Robot::Intake::Intake_();
        }else if (ControllerInputs::Digital::L2){
            Robot::Intake::Outtake();
        }else {
            Robot::Intake::Stop();
        }
        
        // Catapult Activation
        if (ControllerInputs::Digital::X){
            Robot::Catapult::TurnCatapultOn();
        }else {
            Robot::Catapult::TurnCatapultOff();
        }
        // Resset Cata Activation
        if (ControllerInputs::Digital::New::Right){
            Robot::Catapult::ResetCatapult();
        }

        // Delay to save rescources
        pros::delay(dt);
    }
}

