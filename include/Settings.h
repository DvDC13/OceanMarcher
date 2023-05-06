#pragma once

#include "Vector2.h"
#include "Vector3.h"

namespace Settings
{
    inline constexpr int NUM_FRAMES = 480;
    inline constexpr int SCREEN_WIDTH = 512;
    inline constexpr int SCREEN_HEIGHT = 512;
    inline constexpr int NUM_SAMPLES = 1;

    inline constexpr double minSunP = -4.0;
    inline constexpr double maxSunP = 1.5;

    inline constexpr int heightMapWidth = 1024;
    inline constexpr int heightMapHeight = 1024;

    inline constexpr double windSpeed = 4.5;
    inline Utils::Vector2 windDirection(-1.0, -1.0);
    inline constexpr double gravity = 9.81;
    inline constexpr double Lx = 256;
    inline constexpr double Ly = 256;
} // namespace Settings