#include "api.h"
#include "lemlib/api.hpp"
#include "utils.h"
using namespace pros;


/**
* @brief Robot class, contains all robot related definitions and functions (all static members) 
*/
class Robot{
    public:
        /**
        * @brief Contains the autonomous related memebers
        */
        class autonomous{
            public:
                /** @brief The autonomous routine to run on auton start*/
                static AutonomousType autonType;
                /** @brief Runs the specified autonomous routine*/
                static void RunAuton();
                /** @brief True if the auton is finished, false if not*/
                static bool IsDone;
        };

        /**
        * @brief All motors on the robot
        */
        class Motors{
            public:
                /** @brief The catapult motor*/
                static Motor Catapult;
                /** @brief The intake motors*/
                static MotorGroup Intake;
                /** @brief The left drive motors*/
                static MotorGroup leftDrive;
                /** @brief The right drive motors*/
                static MotorGroup rightDrive;
                /** @brief The lemlib drivetrain, for accesing both left and right drive motors simultaneously*/
                static lemlib::Drivetrain drivetrain;
        };
        /** @brief Intake class, contains all members for the utilisation of motors*/
        class Intake{
            public:
                /** @brief 1 for Intaking, 0 for stopped, -1 for Outtaking*/
                static int Direction;
                /** @brief Starts outtaking*/
                static void Outtake();
                /** @brief Starts intaking*/
                static void Intake_();
                /** @brief Stops intake*/
                static void Stop();

                /**
                * @brief Intakes for certain ammount of time
                * @param time The time for intaking
                * @param async Wether the method runs asynchronously or not (false by defualt)
                */
                static void IntakeFor(float time, bool async=false);

                /**
                * @brief Outtakes for certain ammount of time
                * @param time The time for outtaking
                * @param async Wether the method runs asynchronously or not (false by defualt)
                */
                static void OuttakeFor(float time, bool async=false);
                
                /** 
                * @brief Move forward while intaking triball
                * @param dist How far to move forward, inches (3.5'' by default)
                * @param async Wether the method runs asynchronously or not (false by defualt)
                */
                static void IntakeTriball(float dist=3.5, bool async=true);
        };
        /** @brief Contains all ADI Digital Outs for the pistons*/
        class Pistons{
            public:
                /** @brief Both of the wings' pistons*/
                static const ADIDigitalOut WingPistons;
                /** @brief The piston for the balance mech*/
                static const ADIDigitalOut BalanceMech;
        };
        /** @brief Class that contains all functionality for wings*/
        class Wings{
            public:
                /** @brief True if wings are extended, false if not*/
                static bool EXTENDED;
                /** @brief Drops wings (extended to true)*/
                static void DropWings();
                /** @brief Retracts wings (extended to false)*/
                static void RetractWings();
                /** @brief Toggles wings*/
                static void ToggleWings();

                /**
                * @brief Drops wings for specified time period
                * @param time Time for wings to be down
                * @param async Wether to do the task asynchronously or not
                */
                static void DropWingsFor(double time, bool async=false);
                // TODO: Implement below
                //static void DropWingsFor(float Distance);
        };
        /** @brief Contains functionality for balance mech*/
        class BalanceMech{
            public:
                /** @brief Wether the balance mech is dropped or not*/
                static bool DROPPED;
                /** @brief Wether the balance can drop (only in last 30 seconds)*/
                static bool CanDrop;
                /** @brief Drops balance mech (only if DROPPED == true)*/
                static void DropBalance();

        };
        /** @brief Contains the robot's dimensions*/
        class Dimensions{
            public:
                /** @brief Distance between left and right drive wheels*/
                static const float TrackWidth;
                /** @brief Diameter of drive wheels*/
                static const float WheelDiam;
                /** @brief Output RPM of wheels (after gearing)*/
                static const float WheelRPM;
                /** @brief Total width of robot*/
                static const float RobotWidth;
                /** @brief Total length of robot*/
                static const float RobotLength;
        };
        /** @brief Contains all tunable values*/
        class Tunables{
            public:
                /** @brief PID/tunable values for the lateral movement controller (forwards and backwards)*/
                static lemlib::ControllerSettings linearController;
                /** @brief PID/tunable values for the angular movement controller*/
                static lemlib::ControllerSettings angularController;
                /** @brief Chase power for lemlib*/
                static const float ChasePower;
        };
        /** Contains all the sensors used*/
        class Sensors{
            public:
                /** @brief The robot's IMU*/
                static IMU imu;
                /** @brief All odometry sensors for lemlib*/
                static const lemlib::OdomSensors odomSensors;
        };
        /** @brief Contains members for funcionality of catapult*/
        class Catapult{
            public:
                /** @brief Speed of catapult between 0 and 1*/
                static float CatapultSpeed;
                /** @brief How many times the catapult shoots per motor revolution*/
                static const float ShotsPerRotation;
                /** @brief Wether the catapult is cycling or not*/
                static bool IsOn;
                /** @brief Starts cycling catapult*/
                static void TurnCatapultOn();
                /** @brief Stops cycling catapult*/
                static void TurnCatapultOff();

                /** 
                * @brief Use catapult for ammount of time
                * @param time Time to use catapult for
                * @param async Wether to run the task asynchronoulsy or not
                */
                static void UseCatapultFor(double time, bool async=false);

                /** 
                * @brief Use catapult for specified ammound of matchloads
                * @param matchloads How many matchloads to run the catapult for
                * @param async Wether to run the task asynchronoulsy or not
                */
                static void UseCatapultFor(int matchloads, bool async=false);

                /**
                * @brief Matchload all given matchloads (22) + the error margin
                * @param errorMargin How many extra matchloads to run for to compensate for human error
                */
                static void MatchLoad(int errorMargin);
                /** @brief Ressets catapult to avoid rubber band straining*/
                static void ResetCatapult();
        };
        
        /** @brief Contains all members for driver control*/
        class OpControl{
            public:
                /** @brief The driver control scheme to use*/
                static const DriverType driverType;
                /** @brief The main driver control loop*/
                static void DriverControlLoop();
                /** @brief Time delay in driver control loop*/
                static const float dt;
                /** @brief The controller to be used*/
                static const Controller Master;
                /** @brief Wether to break the loop or not*/
                static bool breakLoop;
                /** @brief Controller deadzone for throttle*/
                static const float ThrottleDeadzone;
                /** @brief Controller deadzone for turning*/
                static const float TurnDeadzone;
                /** @brief Wether movement inputs are idle*/
                static bool Idle;
                /** @brief How long after remaining idle to set drivetrain to HOLD*/
                static const float HOLDThreshold;
            protected:
                /** @brief Applies deadzones and updates Idle value
                * @param a The first/throttle input
                * @param b The second/turn input
                * @returns a and b with applied deadzones*/
                static float* ProcessMovementInputs(float a, float b);
                
                /** @brief Handles all movement iunputs*/
                static void DrivetrainMovement();
        };
        /** @brief The lemlib chassis*/
        static lemlib::Chassis chassis;
};