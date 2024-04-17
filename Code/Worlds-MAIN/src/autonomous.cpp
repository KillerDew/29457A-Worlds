#include "lemlib/api.hpp"
#include "api.h"
#include "pros/llemu.hpp"
#include "pros/motors.h"
#include "usr/fieldDimensions.h"

using namespace FieldDimensions;


//! CHECK BEFORE MATCH:
AutonomousType Robot::autonomous::autonType = OffensiveSafe3Ball;

bool Robot::autonomous::IsDone = false;

void DefensiveAuton(){
    // TODO
    Robot::chassis.waitUntilDone();
    return;
}
void WIPOffensive(){
	Robot::chassis.setPose(Offensive3BallSafeStart, false);

    // Pick Up first tri-ball
    Robot::Intake::Intake_();
    Robot::chassis.moveToPose(3, -60, LEFT, 500);
    Robot::chassis.waitUntilDone();
    Robot::Intake::Stop();

    // Navigate to ML bar
    Robot::chassis.moveToPose(48.8, -58.2, 225, 3000, {.forwards=false, .lead=0.2});
    Robot::chassis.waitUntilDone();
    // Take ML tri-ball
    Robot::Wings::DropWings();
    Robot::chassis.moveToPose(58.9, -48.4, 196.2, 750, {.forwards=false, .lead=0.2, .minSpeed=80});
    Robot::chassis.waitUntilDone();
    Robot::Wings::RetractWings();

    // Ram ML and starting Tri-ball
    Robot::chassis.moveToPose(63, -38, DOWN, 500, {.forwards=false, .lead=0.2, .minSpeed=60});
    Robot::chassis.moveToPose(63, -45, DOWN, 300, {.forwards=true, .minSpeed=40});
    Robot::chassis.moveToPose(63, -38, DOWN, 300, {.forwards=false, .minSpeed=90});
    //
    // Score Intaked tri-ball
    Robot::chassis.moveToPose(63, -46, DOWN, 300);
    Robot::chassis.turnToHeading(UP, 300, false);
    Robot::Intake::Outtake();
    Robot::chassis.moveToPose(63, -38, UP, 400, {}, false);
    Robot::Intake::Stop();
}
void OffensiveSafeAuton(){
    // TODO
    WIPOffensive();
    Robot::chassis.waitUntilDone();
    return;
}
void Robot::autonomous::RunAuton(){
    IsDone = false;
    AutonomousType autType = Robot::autonomous::autonType;
    if (autType == Defensive){
        DefensiveAuton();
    }else if (autType == OffensiveSafe3Ball){
        OffensiveSafeAuton();
    }
    Robot::autonomous::IsDone = true;
}