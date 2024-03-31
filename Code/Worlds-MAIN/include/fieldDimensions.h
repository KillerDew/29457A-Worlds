#include "robot.h"
#include "lemlib/api.hpp"
#include <cmath>

namespace FieldDimensions{
    enum HEADING {
        UP = 0,
        RIGHT = 90,
        DOWN = 180,
        LEFT = 270
    };


    constexpr float MAX_X = 72;
    constexpr float MAX_Y = 72;
    constexpr float MIN_X = -72;
    constexpr float MIN_Y = -72;
    constexpr float TILE_LENGTH = 24;
    constexpr float TILE_RADIUS = TILE_LENGTH / 2;

    const inline lemlib::Pose OffensiveStartingPos = {20, -60, LEFT};
    // TODO:
    const inline lemlib::Pose DefensiveStartingPos ={0,0,0};
    const inline lemlib::Pose AutonSkillsStartingPos{0,0,0};
}