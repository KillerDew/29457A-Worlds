#include "main.h"
#include "pros/adi.hpp"
#include "pros/misc.h"
#include "pros/misc.hpp"
#include "pros/motors.h"
#include "pros/motors.hpp"
#include <sys/syslimits.h>
#include "pros/rtos.hpp"
#include "robot.h"

/////
// For installation, upgrading, documentations and tutorials, check out our website!
// https://ez-robotics.github.io/EZ-Template/
/////


// Chassis constructor
ez::Drive chassis (
  // Left Chassis Ports (negative port will reverse it!)
  //   the first port is used as the sensor
  {-11, -13, -14}

  // Right Chassis Ports (negative port will reverse it!)
  //   the first port is used as the sensor
  ,{1, 2, 3}

  // IMU Port
  ,15

  // Wheel Diameter (Remember, 4" wheels without screw holes are actually 4.125!)
  ,3.25

  // Cartridge RPM
  ,600

  // External Gear Ratio (MUST BE DECIMAL) This is WHEEL GEAR / MOTOR GEAR
  // eg. if your drive is 84:36 where the 36t is powered, your RATIO would be 84/36 which is 2.333
  // eg. if your drive is 60:36 where the 36t is powered, your RATIO would be 60/36 which is 0.6
  // eg. if your drive is 36:60 where the 60t is powered, your RATIO would be 36/60 which is 0.6
  ,60.0/36.0
);
pros::Controller Master (pros::E_CONTROLLER_MASTER);
pros::Motor Robot::Intake (12, pros::E_MOTOR_GEAR_600);
//pros::MotorGroup Robot::Intake ({pros::Motor(12, pros::E_MOTOR_GEAR_600), pros::Motor(-20, pros::E_MOTOR_GEAR_600)}) // MUST SET SECOND MOTOR TO CORRECT PORT AND UNCOMMENT IN robot.h;
pros::ADIDigitalOut Robot::Wings ('a');
bool Robot::WingsExtended = false;
pros::ADIDigitalOut BalanceMech('b');
pros::ADIDigitalOut PassiveA ('c');
bool WingsExtended = false;
bool PassiveExtended = false;


/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
  BalanceMech.set_value(true);
  // Print our branding over your terminal :D
  ez::ez_template_print();
  
  pros::delay(500); // Stop the user from doing anything while legacy ports configure

  // Configure your chassis controls
  chassis.opcontrol_curve_buttons_toggle(true); // Enables modifying the controller curve with buttons on the joysticks
  chassis.opcontrol_drive_activebrake_set(2); // Sets the active brake kP. We recommend 2.
  chassis.opcontrol_curve_sd_initialize();
  chassis.opcontrol_joystick_threshold_set(5);
  default_constants(); // Set the drive to your own constants from autons.cpp!

  // These are already defaulted to these buttons, but you can change the left/right curve buttons here!
  // chassis.opcontrol_curve_buttons_left_set (pros::E_CONTROLLER_DIGITAL_LEFT, pros::E_CONTROLLER_DIGITAL_RIGHT); // If using tank, only the left side is used. 
  // chassis.opcontrol_curve_buttons_right_set(pros::E_CONTROLLER_DIGITAL_Y,    pros::E_CONTROLLER_DIGITAL_A);

  // Autonomous Selector using LLEMU
  ez::as::auton_selector.autons_add({
    Auton("Defensive", Defensive),
    Auton("Safe Far Side", SafeFarSide),
    Auton("Example Drive\n\nDrive forward and come back.", drive_example),
    Auton("Example Turn\n\nTurn 3 times.", turn_example),
    Auton("Drive and Turn\n\nDrive forward, turn, come back. ", drive_and_turn),
    Auton("Drive and Turn\n\nSlow down during drive.", wait_until_change_speed),
    Auton("Swing Example\n\nSwing in an 'S' curve", swing_example),
    Auton("Combine all 3 movements", combining_movements),
    Auton("Interference\n\nAfter driving forward, robot performs differently if interfered or not.", interfered_example),
  });
  // Initialize chassis and auton selector
  chassis.initialize();
  ez::as::initialize();
  master.rumble(".");
}



/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {
  // . . .
}



/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {
  // . . .
}



/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
  Robot::Intake.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  chassis.pid_targets_reset(); // Resets PID targets to 0
  chassis.drive_imu_reset(); // Reset gyro position to 0
  chassis.drive_sensor_reset(); // Reset drive sensors to 0
  chassis.drive_brake_set(pros::E_MOTOR_BRAKE_HOLD); // Set motors to hold.  This helps autonomous consistency

  ez::as::auton_selector.selected_auton_call(); // Calls selected auton from autonomous selector
}



/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
  Robot::WingsExtended = false;
  Robot::Wings.set_value(false);
  // This is preference to what you like to drive on
  chassis.drive_brake_set(pros::E_MOTOR_BRAKE_COAST);
  while (true) {
    // PID Tuner
    // After you find values that you're happy with, you'll have to set them in auton.cpp
    if (!pros::competition::is_connected()) {
      // Trigger the selected autonomous routine
      if (master.get_digital_new_press(DIGITAL_L1)) 
        autonomous();

      chassis.pid_tuner_iterate(); // Allow PID Tuner to iterate
    } 

    //chassis.opcontrol_tank(); // Tank control
    //chassis.opcontrol_arcade_standard(ez::SPLIT); // Standard split arcade
    chassis.opcontrol_arcade_standard(ez::SINGLE); // Standard single arcade
    // chassis.opcontrol_arcade_flipped(ez::SPLIT); // Flipped split arcade
    // chassis.opcontrol_arcade_flipped(ez::SINGLE); // Flipped single arcade

  
    if (Master.get_digital(pros::E_CONTROLLER_DIGITAL_L2)){
      Robot::Intake = 127;
    }
    else if (Master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)){
      Robot::Intake = -127;
    }else {
      Robot::Intake=0;
    }

    if (Master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1)){
      Robot::WingsExtended = !Robot::WingsExtended;
      Robot::Wings.set_value(Robot::WingsExtended);
    }
    if (Master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN)){
      PassiveExtended = !PassiveExtended;
      PassiveA.set_value(PassiveExtended);
    }
    if (Master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)){
      BalanceMech.set_value(false);
    }
    // . . .
    // Put more user control code here!
    // . . .

    pros::delay(ez::util::DELAY_TIME); // This is used for timer calculations!  Keep this ez::util::DELAY_TIME
  }
}
