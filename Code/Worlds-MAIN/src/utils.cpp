#include "api.h"
#include "lemlib/api.hpp"
#include "utils.h"

double Timer::GetElapsed(){
    return pros::millis()-StartTime;
}
void Timer::Reset(float Override){
    if (Override==-1){
        StartTime=pros::millis();
    }else{
        StartTime=Override;
    }
}
void Timer::waitUntil(double target){
    while (GetElapsed() < target){
        pros::delay(10);
    }
}
void Timer::TurnToAfter(double target, bool* value, bool setTo){
    pros::Task([&](){
        while (GetElapsed() < target){
            pros::delay(20);
        }
        *value = setTo;
    });
    pros::delay(5);
}
Timer::Timer(){
    StartTime = pros::millis();
}


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