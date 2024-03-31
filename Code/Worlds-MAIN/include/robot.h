#include "api.h"
#include "lemlib/api.hpp"
#include "pros/misc.hpp"
#include "utils.h"
using namespace pros;


class Robot{
    public:
        class autonomous{
        public:
            static AutonomousType autonType;
            static void RunAuton();
            static bool IsDone;
        };

        /*
        *@brief Motors
        */
        class Motors{
            public:
                static Motor Catapult;
                static MotorGroup Intake;
                static MotorGroup leftDrive;
                static MotorGroup rightDrive;
                static lemlib::Drivetrain drivetrain;
        };
        class Intake{
            public:
                static int Direction;
                static void Outtake();
                static void Intake_();
                static void Stop();
                static void IntakeFor(float time, bool async=false);
                static void OuttakeFor(float time, bool async=false);
                static void IntakeTriball(float dist=3.5, bool async=true);
        };
        class Pistons{
            public:
                static const ADIDigitalOut WingPistons;
                static const ADIDigitalOut BalanceMech;
        };
        class Wings{
            public:
                static bool EXTENDED;
                static void DropWings();
                static void RetractWings();
                static void ToggleWings();
                static void DropWingsFor(double time, bool async=false);
                // TODO: Implement below
                //static void DropWingsFor(float Distance);
        };
        class BalanceMech{
            public:
                static bool DROPPED;
                static bool CanDrop;
                static void DropBalance();

        };
        class Dimensions{
            public:
                static const float TrackWidth;
                static const float WheelDiam;
                static const float WheelRPM;
                
                static const float ChasePower;

                static const float RobotWidth;
                static const float RobotLength;
        };
        class Tunables{
            public:
                static lemlib::ControllerSettings linearController;
                static lemlib::ControllerSettings angularController;
                static const float ChasePower;
        };
        class Sensors{
            public:
                static IMU imu;
                static const lemlib::OdomSensors odomSensors;
        };
        class Catapult{
            public:
                static float CatapultSpeed;
                static const float ShotsPerRotation;
                static bool IsOn;
                static void TurnCatapultOn();
                static void TurnCatapultOff();
                static void UseCatapultFor(double time, bool async=false);
                static void UseCatapultFor(int matchloads, bool async=false);
                static void MatchLoad(int errorMargin);
                static void ResetCatapult();
        };
        class OpControl{
            public:
                static const DriverType driverType;
                static void DriverControlLoop();
                static const float dt;
                static const Controller Master;
                static bool breakLoop;
                static const float ThrottleDeadzone;
                static const float TurnDeadzone;
                static bool Idle;
                static const float HOLDThreshold;
            protected:
                static float* ProcessMovementInputs(float a, float b);
                static void DrivetrainMovement();
        };
        static lemlib::Chassis chassis;
};