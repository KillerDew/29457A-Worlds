#include "api.h"
#include "usr/Inputs.h"


#pragma region Inits
    //* Initialize all variables
    float ControllerInputs::Analogue::LeftX=0;
    float ControllerInputs::Analogue::LeftY=0;
    float ControllerInputs::Analogue::RightX=0;
    float ControllerInputs::Analogue::RightY=0;

    bool ControllerInputs::Digital::New::L1=false;
    bool ControllerInputs::Digital::New::L2=false;
    bool ControllerInputs::Digital::New::R1=false;
    bool ControllerInputs::Digital::New::R2=false;
    bool ControllerInputs::Digital::New::X=false;
    bool ControllerInputs::Digital::New::Y=false;
    bool ControllerInputs::Digital::New::B=false;
    bool ControllerInputs::Digital::New::A=false;
    bool ControllerInputs::Digital::New::Down=false;
    bool ControllerInputs::Digital::New::Up=false;
    bool ControllerInputs::Digital::New::Left=false;
    bool ControllerInputs::Digital::New::Right=false;

    bool ControllerInputs::Digital::L1=false;
    bool ControllerInputs::Digital::L2=false;
    bool ControllerInputs::Digital::R1=false;
    bool ControllerInputs::Digital::R2=false;
    bool ControllerInputs::Digital::X=false;
    bool ControllerInputs::Digital::Y=false;
    bool ControllerInputs::Digital::B=false;
    bool ControllerInputs::Digital::A=false;
    bool ControllerInputs::Digital::Down=false;
    bool ControllerInputs::Digital::Up=false;
    bool ControllerInputs::Digital::Left=false;
    bool ControllerInputs::Digital::Right=false;
#pragma endregion

// Functions to assign variables at runtime
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
    Digital::A = controller.get_digital(pros::E_CONTROLLER_DIGITAL_A);
    Digital::B = controller.get_digital(pros::E_CONTROLLER_DIGITAL_B);
    Digital::X = controller.get_digital(pros::E_CONTROLLER_DIGITAL_X);
    Digital::Y = controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y);

    Digital::L1 = controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1);
    Digital::L2 = controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2);
    Digital::R1 = controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1);
    Digital::R2 = controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2);

    Digital::Up = controller.get_digital(pros::E_CONTROLLER_DIGITAL_UP);
    Digital::Right = controller.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT);
    Digital::Down = controller.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN);
    Digital::Left = controller.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT);
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
