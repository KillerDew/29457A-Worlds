#include "api.h"
#include "Inputs.h"
#include "pros/misc.h"
#include "pros/misc.hpp"

void ControllerInputs::GetNews(pros::Controller controller){
    Digital::New::A = controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A);
    Digital::New::B = controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B);
    Digital::New::X = controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X);
    Digital::New::Y = controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y);

    Digital::New::L1 = controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1);
    Digital::New::L2 = controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1);
    Digital::New::R1 = controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1);
    Digital::New::R2 = controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2);

    Digital::New::Up = controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP);
    Digital::New::Right = controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT);
    Digital::New::Down = controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN);
    Digital::New::Left = controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_LEFT);
}
void ControllerInputs::GetDigis(pros::Controller controller){
    Digital::A = controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A);
    Digital::B = controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B);
    Digital::X = controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X);
    Digital::Y = controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y);

    Digital::L1 = controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1);
    Digital::L2 = controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1);
    Digital::R1 = controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1);
    Digital::R2 = controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2);

    Digital::Up = controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP);
    Digital::Right = controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT);
    Digital::Down = controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN);
    Digital::Left = controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_LEFT);
}
void ControllerInputs::GetAnalogues(pros::Controller controller){
    Analogue::LeftX = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X);
    Analogue::LeftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    Analogue::RightX = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
    Analogue::RightY = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
}
void ControllerInputs::GetInputs(pros::Controller controller){
    GetNews(controller);
    GetDigis(controller);
    GetAnalogues(controller);
}
