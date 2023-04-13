#include "Camera.h"

namespace Rendering
{
    Camera::Camera(Utils::Point3 look_from, Utils::Point3 look_at, Utils::Vector3 up, double vertical_fov, double aspect_ratio)
        : m_look_from(look_from),
        m_look_at(look_at),
        m_up(up),
        m_bottom_left_corner(0, 0, 0),
        m_horizontal(0, 0, 0),
        m_vertical(0, 0, 0)
    {
        auto theta = degreesToRadians(vertical_fov);
        auto h = tan(theta / 2);
        auto viewport_height = 2.0 * h;
        auto viewport_width = aspect_ratio * viewport_height;

        auto w = Utils::normalize(m_look_from - m_look_at);
        auto u = Utils::normalize(Utils::cross(m_up, w));
        auto v = Utils::cross(w, u);

        m_horizontal = viewport_width * u;
        m_vertical = viewport_height * v;
        m_bottom_left_corner = m_look_from - m_horizontal / 2 - m_vertical / 2 - w;
    }

    Rendering::Ray Camera::getRay(double u, double v) const
    {
        return Rendering::Ray(m_look_from, m_bottom_left_corner + u * m_horizontal + v * m_vertical - m_look_from, Utils::Color3(1.0, 1.0, 1.0));
    }

    double Camera::degreesToRadians(double degrees) const
    {
        return degrees * M_PI / 180;
    }
}