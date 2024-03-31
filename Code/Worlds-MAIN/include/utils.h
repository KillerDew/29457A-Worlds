
#include <string>
class Timer{
    public:
        double StartTime;
        double GetElapsed();
        void waitUntil(double target);
        void Reset(float Override=-1);
        void TurnToAfter(double target, bool* value, bool setTo=true);
        Timer();

};
enum DriverType{
    Arcade=0,
    SplitArcade=1,
    Curvature=2,
    SplitCurvature=3,
    Tank=4,
};

enum AutonomousType{
    OffensiveSafe=0,
    Defensive=1
};
class Utils{
    public:
        static std::string DTypeSTR(DriverType type);
        static std::string ATypeSTR(AutonomousType type);
};