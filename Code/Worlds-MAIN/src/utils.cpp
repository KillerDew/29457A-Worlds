#include "api.h"
#include "lemlib/api.hpp"
#include "usr/utils.h"

// UTILS: extra functions and classes

// Timer class --

// Returns elapsed time from start time
double Timer::GetElapsed(){
    return pros::millis()-StartTime;
}
// Reset Timer
// If the override is -1, set start time to current time (else the override)
void Timer::Reset(float Override){
    if (Override==-1){
        StartTime=pros::millis();
    }else{
        StartTime=Override;
    }
}
// Waits for target elapsed time using a loop
void Timer::waitUntil(double target){
    while (GetElapsed() < target){
        pros::delay(10);
    }
}
// Turns variable to specified value after target time
void Timer::TurnToAfter(double target, bool* value, bool setTo){
    pros::Task([&](){
        waitUntil(target);
        *value = setTo;
    });
    pros::delay(5);
}
// Constructer, sets start time to override OR current time
Timer::Timer(float Override){
    Reset(Override);
}
// --

// Converts driver type to str using switch
std::string Utils::DTypeSTR(DriverType type){
    switch (type) {
        case 0:
            return "Arcade";
            break;
        case 1:
            return "Split Arcade";
            break;
        case 2:
            return "Cheesy";
            break;
        case 3:
            return "Split Cheesy";
            break;
        case 4:
            return "Tank";
            break;
        default:
            return "?";
    }
}
// Converts auton type to str using switch
std::string Utils::ATypeSTR(AutonomousType type){
    switch (type) {
        case 0:
            return "Safe 3 Ball (Far)";
            break;
        case 1:
            return "Defensive";
            break;
        default:
            return "?";
    }
}