#include "api.h"
#include "lemlib/api.hpp"
#include "usr/robot.h"

// Linear controller
lemlib::ControllerSettings Robot::Tunables::linearController(10,
                                                             0,
                                                             3,
                                                             3,
                                                             1,
                                                             100,
                                                             3,
                                                             500,
                                                             20                                   
);
// ANgular controller
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
// Chase power (8 due to use of traction wheels)
const float Robot::Tunables::ChasePower = 8;