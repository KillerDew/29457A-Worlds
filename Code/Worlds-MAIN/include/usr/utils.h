#include <string>


/** @brief Timer class, for running time-dependant tasks*/
class Timer{
    public:
        /** @brief The time of timer being started or reset.*/
        double StartTime;

        /** @brief Gets elsapsed time from start time (time - StartTime)*/
        double GetElapsed();

        /**
        * @brief Waits for a target elapsed time 
        * @param target The target elapsed time
        */
        void waitUntil(double target);

        /**
        * @brief Resets start time to current time or the override time
        * @param Ovveride Ovveride the start time
        */
        void Reset(float Override=-1);

        /** 
        * @brief Turns value (pointer) to true or false once at target elapsed
        * @param target Target elapsed time
        * @param value Pointer to boolean variable to change after target elapsed
        * @param setTo What to set the value to after target elapsed
        */
        void TurnToAfter(double target, bool* value, bool setTo=true);

        Timer();

};
/** @brief Driver control scheme enum*/
enum DriverType{
    Arcade=0,
    SplitArcade=1,
    Curvature=2,
    SplitCurvature=3,
    Tank=4,
};
/** @brief Auton type enum*/
enum AutonomousType{
    OffensiveSafe3Ball=0,
    Defensive=1
};

/** @brief Contains peripheral useful functions*/
class Utils{
    public:
        /**
        * @brief Outputs the the name of the specified driver control scheme as a string
        * @param type The driver control sheme
        */
        static std::string DTypeSTR(DriverType type);

        /**
        * @brief Outputs the the name of the specified autonomous routine as a string
        * @param type The autonomous type
        */
        static std::string ATypeSTR(AutonomousType type);
};