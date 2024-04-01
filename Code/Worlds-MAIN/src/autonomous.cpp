#include "lemlib/api.hpp"
#include "api.h"
#include "fieldDimensions.h"

using namespace FieldDimensions;


//! CHECK BEFORE MATCH:
AutonomousType Robot::autonomous::autonType = OffensiveSafe3Ball;

lemlib::Chassis* Chassis = &Robot::chassis;
bool Robot::autonomous::IsDone = false;

void DefensiveAuton(){
    Chassis->waitUntilDone();
    return;
}
void WIPOffensive(){
	Chassis->setPose(OffensiveStartingPos);
    Chassis->moveToPose(3, -60, LEFT, 500);
    Chassis->moveToPose(48.8, -58.2, 225, 3000, {.forwards=false, .lead=0.2});
    Chassis->waitUntilDone();
    Robot::Wings::DropWings();
    Chassis->moveToPose(58.9, -48.4, 196.2, 750, {.forwards=false, .lead=0.2, .minSpeed=80});
    Chassis->waitUntilDone();
    Robot::Wings::RetractWings();
    Chassis->moveToPose(63, -38, DOWN, 500, {.forwards=false, .lead=0.2, .minSpeed=60});
    Chassis->moveToPose(63, -45, DOWN, 300, {.forwards=true, .minSpeed=40});
    Chassis->moveToPose(63, -38, DOWN, 300, {.forwards=false, .minSpeed=90});
    Chassis->moveToPose(63, -46, DOWN, 300);
    Chassis->turnToHeading(UP, 300, false);
    Robot::Intake::Outtake();
    Chassis->moveToPose(63, -38, UP, 400, {}, false);
    Robot::Intake::Stop();
}
void OffensiveSafeAuton(){
    WIPOffensive();
    Chassis->waitUntilDone();
    return;
}
void Robot::autonomous::RunAuton(){
    Robot::autonomous::IsDone = false;
    AutonomousType autType = Robot::autonomous::autonType;
    if (autType == Defensive){
        DefensiveAuton();
    }else if (autType == OffensiveSafe3Ball){
        OffensiveSafeAuton();
    }
    Robot::autonomous::IsDone = true;
}