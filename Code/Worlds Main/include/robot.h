#include "main.h"
#include "pros/adi.hpp"


class Robot{
    public:
        static pros::Motor Intake;
        //static pros::MotorGroup Intake;
        static pros::ADIDigitalOut Wings;
        static bool WingsExtended;
};