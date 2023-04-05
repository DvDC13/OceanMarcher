#pragma once

#include "Vector3.h"
#include "Ray.h"

namespace Rendering
{
    class Camera
    {
    public:
        Camera() = default;
        Camera(Utils::Point3 look_from, Utils::Point3 look_at, Utils::Vector3 up, double vertical_fov, double aspect_ratio);

        Rendering::Ray getRay(double u, double v) const;

        double degreesToRadians(double degrees) const;

        inline Utils::Point3 getLookFrom() const { return m_look_from; }
        inline Utils::Point3 getLookAt() const { return m_look_at; }
        inline Utils::Vector3 getUp() const { return m_up; }
        inline Utils::Point3 getBottomLeftCorner() const { return m_bottom_left_corner; }
        inline Utils::Vector3 getHorizontal() const { return m_horizontal; }
        inline Utils::Vector3 getVertical() const { return m_vertical; }

    private:
        Utils::Point3 m_look_from;
        Utils::Point3 m_look_at;
        Utils::Vector3 m_up;

        Utils::Point3 m_bottom_left_corner;
        Utils::Vector3 m_horizontal;
        Utils::Vector3 m_vertical;
    };
}