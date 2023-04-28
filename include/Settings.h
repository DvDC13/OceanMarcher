#pragma once

#include "Vector2.h"
#include "Vector3.h"

namespace Settings
{
    inline constexpr int NUM_FRAMES = 1200;
    inline constexpr int SCREEN_WIDTH = 512;
    inline constexpr int SCREEN_HEIGHT = 512;
    inline constexpr int NUM_SAMPLES = 1;

    inline constexpr int heightMapWidth = 512;
    inline constexpr int heightMapHeight = 512;

    inline constexpr double windSpeed = 31; 
    inline Utils::Vector2 windDirection(-1.0, -1.0);
    inline constexpr double gravity = 9.81;
    inline constexpr double Lx = 1000;
    inline constexpr double Ly = 1000;
} // namespace Settings
