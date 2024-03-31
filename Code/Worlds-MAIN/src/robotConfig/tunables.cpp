#include "api.h"
#include "lemlib/api.hpp"
#include "lemlib/chassis/chassis.hpp"
#include "robot.h"

lemlib::ControllerSettings Robot::Tunables::linearController(10,
                                                             0,
                                                             3,
                                                             3,
                                                             1,
                                                             100,
                                                             3,
                                                             500,
                                                             2                                     
);
lemlib::ControllerSettings Robot::Tunables::angularController(2,
                                                              0,
                                                              10,
                                                              3,
                                                              1,
                                                              100,
                                                              3,
                                                              500,
                                                              0
);
const float Robot::Tunables::ChasePower = 8;