#include "api.h"
#include "robot.h"

bool Robot::BalanceMech::DROPPED = false;
bool Robot::BalanceMech::CanDrop = false;

void Robot::BalanceMech::DropBalance(){
    if (CanDrop){
        DROPPED = true;
        Robot::Pistons::BalanceMech.set_value(DROPPED);
    }
}