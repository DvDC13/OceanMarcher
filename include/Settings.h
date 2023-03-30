#pragma once

#include "Vector2.h"
#include "Vector3.h"

namespace Settings
{
    static constexpr int SCREEN_WIDTH = 200;
    static constexpr int SCREEN_HEIGHT = 100;

    static constexpr double windSpeed = 10.0;
    static Utils::Vector2 windDirection(-1.0, -1.0);
    static constexpr double gravity = 9.81;

    static constexpr double Lx = 8.0;
    static constexpr double Ly = 8.0;

} // namespace Settings
