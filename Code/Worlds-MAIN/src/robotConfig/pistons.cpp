#include "api.h"
#include "usr/robot.h"
using namespace pros;

const ADIDigitalOut Robot::Pistons::WingPistons ('a'); // Wing solenoid on digital port A
const ADIDigitalOut Robot::Pistons::BalanceMech('b'); // Balance mech solenoid on digital port B