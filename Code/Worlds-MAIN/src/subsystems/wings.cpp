#include "api.h"
#include "robot.h"

void Robot::Wings::DropWings(){
    Robot::Wings::EXTENDED = true;
    Robot::Pistons::WingPistons.set_value(true);
}
void Robot::Wings::RetractWings(){
    Robot::Wings::EXTENDED = false;
    Robot::Pistons::WingPistons.set_value(false);
}
void Robot::Wings::ToggleWings(){
    Robot::Wings::EXTENDED = !Robot::Wings::EXTENDED;
    Robot::Pistons::WingPistons.set_value(Robot::Wings::EXTENDED);
}
void Robot::Wings::DropWingsFor(double time, bool async){
    if (async){
        pros::Task ([&](){
            DropWings();
            pros::delay(time);
            RetractWings();
        });
    }else{
        DropWings();
        pros::delay(time);
        RetractWings();
    }
}