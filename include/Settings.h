#pragma once

#include "Vector2.h"
#include "Vector3.h"

namespace Settings
{
    inline constexpr int SCREEN_WIDTH = 500;
    inline constexpr int SCREEN_HEIGHT = 400;

    inline constexpr double windSpeed = 3.5;    
    inline Utils::Vector2 windDirection(-1.0, -1.0);
    inline constexpr double gravity = 9.81;

    inline constexpr double Lx = 8.0;
    inline constexpr double Ly = 8.0;
} // namespace Settings
