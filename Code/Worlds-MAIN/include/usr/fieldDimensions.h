/**
* @file fieldDimensions.h
* @brief Contains common length and dimension values, as well as autonomous starting positions.
* @author Daniel Dew
*/

#include "robot.h"
#include "lemlib/api.hpp"
#include <cmath>

namespace FieldDimensions{
    /**
    * @brief Contains headings for Up (North), Right (East), Down (South) and Left (West)
    */
    enum HEADING {
        UP = 0,
        RIGHT = 90,
        DOWN = 180,
        LEFT = 270
    };

    /** @brief Maximum X value on field*/
    constexpr float MAX_X = 72;
    /** @brief Maximum Y value on field*/
    constexpr float MAX_Y = 72;
    /** @brief Minimum X value on field*/
    constexpr float MIN_X = -72;
    /** @brief Minimum Y value on field*/
    constexpr float MIN_Y = -72;
    /** @brief Length of each tile (2', 24'')*/
    constexpr float TILE_LENGTH = 24;
    /** @brief Radius of each tile (half of tile length, 1', 12'')*/
    constexpr float TILE_RADIUS = TILE_LENGTH / 2;

    /** @brief Starting Position for Safe 3 ball (offensive)*/
    const inline lemlib::Pose Offensive3BallSafeStart = {20, -60, LEFT};

    //TODO
    /** @brief TODO*/
    const inline lemlib::Pose DefensiveStartingPos ={0,0,0};
    /** @brief TODO*/
    const inline lemlib::Pose AutonSkillsStartingPos{0,0,0};
}