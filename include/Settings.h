#pragma once

#include "Vector2.h"
#include "Vector3.h"

namespace Settings
{
    inline constexpr int NUM_FRAMES = 1;
    inline constexpr int SCREEN_WIDTH = 512;
    inline constexpr int SCREEN_HEIGHT = 512;
    // problem when width != height

    inline constexpr double windSpeed = 31; 
    inline Utils::Vector2 windDirection(-1.0, -1.0);
    inline constexpr double gravity = 9.81;

    inline constexpr double Lx = 1000.0;
    inline constexpr double Ly = 1000.0;
} // namespace Settings
