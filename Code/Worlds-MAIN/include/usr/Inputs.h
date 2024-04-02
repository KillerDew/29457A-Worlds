/**
* @file Inputs.h
* @brief Contains class that holds all the controller inputs
* @author Daniel Dew
*/


#include "api.h"
#include "pros/misc.hpp"

/**
* @name Controller Inputs
* @brief Contains all controller inputs in subclasses.
*/
class ControllerInputs{
    public:
        /**
        * @name Analogue Inputs
        * @brief Contains the joystic inputs (from -127 to 127)
        */
        class Analogue{
            public:
                /** @brief Left Joystick X position*/
                static float LeftX;
                /** @brief Left Joystic Y positions*/
                static float LeftY;
                /** @brief Right Joystick X position*/
                static float RightX;
                /** @brief Right Joystic Y position*/
                static float RightY;
        };
        /**
        * @name Digital Inputs
        * @brief Contains discrete (in '::New) and continuous booleans representing each digital input (buttons)
        */
        class Digital{
            public:
            /**
            * @name New Digital Inputs
            * @brief Contains booleans for each of the buttons' new presses (discrete)
            */
                class New{
                    public:
                        static bool L1;
                        static bool L2;
                        static bool R1;
                        static bool R2;
                        static bool X;
                        static bool Y;
                        static bool B;
                        static bool A;
                        static bool Down;
                        static bool Up;
                        static bool Left;
                        static bool Right;
                };
                static bool L1;
                static bool L2;
                static bool R1;
                static bool R2;
                static bool X;
                static bool Y;
                static bool B;
                static bool A;
                static bool Down;
                static bool Up;
                static bool Left;
                static bool Right;
        };
        /**
        * @brief Assigns all inputs in class
        * @param controller The controller to read inputs from
        */
        static void GetInputs(pros::Controller controller);
        //TODO: Implement below
        /**
        * @brief Gets inputs in the background every dt milliseconds. Useful for opcontrol.
        * @param controller The controller to read inputs from
        * @param dt Milliseconds between input reads
        */
        static void ReadInputsContinuously(pros::Controller controller, float dt);
        /**
        * @brief Stops reading inputs continuously
        */
        static void StopReadingInputs();
    private:
        static void GetNews(pros::Controller controller);
        static void GetDigis(pros::Controller controller);
        static void GetAnalogues(pros::Controller controller);
};