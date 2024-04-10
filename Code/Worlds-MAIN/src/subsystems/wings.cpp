#include "api.h"
#include "pros/rtos.hpp"
#include "usr/robot.h"

bool Robot::Wings::EXTENDED = false; // Not extended by defualt
void Robot::Wings::DropWings(){
    // Sets Extended to true and drops wings
    EXTENDED = true;
    Robot::Pistons::WingPistons.set_value(true);
}

void Robot::Wings::RetractWings(){
    // Sets Extended to false and retracts wings
    Robot::Wings::EXTENDED = false;
    Robot::Pistons::WingPistons.set_value(false);
}

void Robot::Wings::ToggleWings(){
    // Toggles wings
    Robot::Wings::EXTENDED = !Robot::Wings::EXTENDED;
    Robot::Pistons::WingPistons.set_value(Robot::Wings::EXTENDED);
}
void Robot::Wings::DropWingsFor(double time, bool async){
    if (async){
        // If async re-calls as a task
        pros::Task ([&](){DropWingsFor(time, false);});
        pros::delay(10);
    }else{
        // Drops wings, waits for time, retracts wings
        DropWings();
        pros::delay(time);
        RetractWings();
    }
}