#include "api.h"


class ControllerInputs{
    public:
        class Analogue{
            public:
                static float LeftX;
                static float LeftY;
                static float RightX;
                static float RightY;
        };
        class Digital{
            public:
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
        static void GetInputs(pros::Controller controller);
    private:
        static void GetNews(pros::Controller controller);
        static void GetDigis(pros::Controller controller);
        static void GetAnalogues(pros::Controller controller);
};