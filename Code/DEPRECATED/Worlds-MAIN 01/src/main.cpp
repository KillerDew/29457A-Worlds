#include "main.h"
#include "lemlib/api.hpp"
#include "pros/adi.hpp"
#include "pros/misc.h"
#include "pros/motors.h"
#include "pros/motors.hpp"
#include "pros/rtos.h"
#include "pros/rtos.hpp"
#include <algorithm>
#include <cmath>
#include <functional>

/*
TODO: Autonomous - Far Side, Close Side, Skills
TODO: Code restructure MAJOR.
*/

// controller
pros::Controller controller(pros::E_CONTROLLER_MASTER);

// drive motors
pros::Motor lF(-17, pros::E_MOTOR_GEARSET_06); // left front motor. port 12, reversed
pros::Motor lM(-18, pros::E_MOTOR_GEARSET_06); // left middle motor. port 11, reversed
pros::Motor lB(-19, pros::E_MOTOR_GEARSET_06); // left back motor. port 1, reversed
pros::Motor rF(7, pros::E_MOTOR_GEARSET_06); // right front motor. port 2
pros::Motor rM(12, pros::E_MOTOR_GEARSET_06); // right middle motor. port 11
pros::Motor rB(9, pros::E_MOTOR_GEARSET_06); // right back motor. port 13

// motor groups
pros::MotorGroup leftMotors({lF, lM, lB}); // left motor group
pros::MotorGroup rightMotors({rF, rM, rB}); // right motor group

// Inertial Sensor on port 2
pros::Imu imu(3);

// drivetrain settings
lemlib::Drivetrain drivetrain(&leftMotors, // left motor group
                              &rightMotors, // right motor group
                              11, // 10 inch track width
                              lemlib::Omniwheel::NEW_325, // using new 3.25" omnis
                              360, // drivetrain rpm is 360
                              8 // chase power is 2. If we had traction wheels, it would have been 8
);

// lateral motion controller
lemlib::ControllerSettings linearController(10, // proportional gain (kP)
                                            0, // integral gain (kI)
                                            3, // derivative gain (kD)
                                            3, // anti windup
                                            1, // small error range, in inches
                                            100, // small error range timeout, in milliseconds
                                            3, // large error range, in inches
                                            500, // large error range timeout, in milliseconds
                                            20 // maximum acceleration (slew)
);

// angular motion controller
lemlib::ControllerSettings angularController(2, // proportional gain (kP)
                                             0, // integral gain (kI)
                                             10, // derivative gain (kD)
                                             3, // anti windup
                                             1, // small error range, in degrees
                                             100, // small error range timeout, in milliseconds
                                             3, // large error range, in degrees
                                             500, // large error range timeout, in milliseconds
                                             0 // maximum acceleration (slew)
);

// sensors for odometry
// note that in this example we use internal motor encoders (IMEs), so we don't pass vertical tracking wheels
lemlib::OdomSensors sensors(nullptr, // vertical tracking wheel 1, set to null
                            nullptr, // vertical tracking wheel 2, set to nullptr as we are using IMEs
                            nullptr, // horizontal tracking wheel 1
                            nullptr, // horizontal tracking wheel 2, set to nullptr as we don't have a second one
                            &imu // inertial sensor
);

// create the chassis
lemlib::Chassis chassis(drivetrain, linearController, angularController, sensors);

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
    pros::lcd::initialize(); // initialize brain screen
    chassis.calibrate(); // calibrate sensors

    // the default rate is 50. however, if you need to change the rate, you
    // can do the following.
    // lemlib::bufferedStdout().setRate(...);
    // If you use bluetooth or a wired connection, you will want to have a rate of 10ms

    // for more information on how the formatting for the loggers
    // works, refer to the fmtlib docs

    // thread to for brain screen and position logging
    pros::Task screenTask([&]() {
        lemlib::Pose pose(0, 0, 0);
        while (true) {
            // print robot location to the brain screen
            pros::lcd::print(0, "X: %f", chassis.getPose().x); // x
            pros::lcd::print(1, "Y: %f", chassis.getPose().y); // y
            pros::lcd::print(2, "Theta: %f", chassis.getPose().theta); // heading
            // log position telemetry
            lemlib::telemetrySink()->info("Chassis pose: {}", chassis.getPose());
            // delay to save resources
            pros::delay(50);
        }
    });
}

/**
 * Runs while the robot is disabled
 */
void disabled() {}

/**
 * runs after initialize if the robot is connected to field control
 */
void competition_initialize() {}
pros::ADIDigitalOut Wings ('a');
pros::ADIDigitalOut BalanceMech ('b');
pros::Motor Intake1 (11);
pros::Motor Intake2 (-1);
pros::MotorGroup Intake ({Intake1, Intake2});
pros::Motor Catapult (6, pros::E_MOTOR_GEAR_RED);
float Cataspeed = 0.4;


void Safe3BallFar(){
	// * Work In Progress
	chassis.setPose(0, 0, 90, false);
	chassis.moveToPose(5, 0, 90, 500, {.forwards=true, .maxSpeed=40}, true);
	Intake = 127;
	chassis.waitUntilDone();
	Intake.brake();
	chassis.moveToPose(-40, 0, 90, 2000, {.forwards=false});
	chassis.moveToPose(-46, -12.5, 45, 1000, {.forwards=false});

}

void (*AutonFunc)() = &Safe3BallFar;
void autonomous() {
	Intake.set_brake_modes(pros::E_MOTOR_BRAKE_HOLD);
	AutonFunc();
}
bool IsIdle;
// Controlling Driving Type
void CurvatureSplit(){
	int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
	int rightX = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
	if (leftY==0&&rightX==0)
		IsIdle = true;
	else IsIdle = false;
	chassis.curvature(leftY, rightX, 2.7);
}
void Curvature(){
	int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
	int leftX = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
	if (leftY==0&&leftX==0)
		IsIdle = true;
	else IsIdle = false;
	chassis.curvature(leftY, leftX, 2.7);
}
void Tank(){
	int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
	int rightY = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
	if (leftY==0&&rightY==0)
		IsIdle = true;
	else IsIdle = false;
	chassis.tank(leftY, rightY);
}
void ArcadeSplit(){
	int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
	int rightX = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
	if (leftY==0&&rightX==0)
		IsIdle = true;
	else IsIdle = false;
	chassis.arcade(leftY, rightX, 2.7);
}
void Arcade(){
	int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
	int leftX = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X);
	if (leftY==0&&leftX==0)
		IsIdle = true;
	else IsIdle = false;
	chassis.arcade(leftY, leftX, 2.7);
}

void (*DriverFunction)() = &Curvature;

/**
 * Runs in driver control
 */
void opcontrol() {
	autonomous();
	double startTime = pros::millis();
	double elapsed = 0;
	bool WingsExtended = false;
	bool BalanceDeployed = false;
	Wings.set_value(false);
	Catapult.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	Intake.set_brake_modes(pros::E_MOTOR_BRAKE_HOLD);
	chassis.setBrakeMode(pros::E_MOTOR_BRAKE_COAST);

	double IdleTime = pros::c::millis();
	//pros::Task(TickUpTimer, (void*)"0.005", "Elpased Timer");
    // controller
    // loop to continuously update motors
    while (true) {
		elapsed = pros::millis()-startTime;
		elapsed /= 1000; // Converts to seconds


        DriverFunction(); // handles drivetrain controls;

		if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1)){
			WingsExtended = !WingsExtended;
			Wings.set_value(WingsExtended);
		}
		
		if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)){
			Intake = -127;
		}else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)){
			Intake = 127;
		}else{
			Intake = 0;
		}

		if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B) && (elapsed >= 65 || controller.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN))){
			BalanceDeployed = !BalanceDeployed;
			BalanceMech.set_value(BalanceDeployed);
		}

		if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_X)){
			Catapult.move(-127*Cataspeed);
		}else Catapult=0;

		if (IsIdle){
			if (pros::c::millis()-IdleTime >= 500){
				chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);
			}
		}else{
			IdleTime = pros::c::millis();
			chassis.setBrakeMode(pros::E_MOTOR_BRAKE_COAST);
		}


        // delay to save resources
        pros::delay(10);
    }
}