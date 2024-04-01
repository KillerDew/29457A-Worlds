#include "main.h"
#include "robot.h"
#include "lemlib/api.hpp"

/*
TODO: Test Code
TODO: Comment ALL Code
TODO: Autonomous
*/

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();

	lcd::print(3, "Calibrating...");
	Robot::chassis.calibrate();
	pros::delay(2000);
	lcd::print(2, "Calibrated!");

	pros::Task screenTask([&]() {
        lemlib::Pose pose(0, 0, 0);
        while (true) {
            // print robot location to the brain screen
            pros::lcd::print(0, "X: %f", Robot::chassis.getPose().x); // x
            pros::lcd::print(1, "Y: %f", Robot::chassis.getPose().y); // y
            pros::lcd::print(2, "Theta: %f", Robot::chassis.getPose().theta); // heading
            // log position telemetry
            lemlib::telemetrySink()->info("Chassis pose: {}", Robot::chassis.getPose());
            // delay to save resources
            pros::delay(50);
        }
    });
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {
	lcd::print(3, "Disabled");
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
void competition_initialize() {}

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
	lcd::print(3, "Auton: {}", Utils::ATypeSTR(Robot::autonomous::autonType));
	Robot::autonomous::RunAuton();
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
	lcd::print(3, "Driver Control: {}", Utils::DTypeSTR(Robot::OpControl::driverType));
	Robot::OpControl::DriverControlLoop();
}

