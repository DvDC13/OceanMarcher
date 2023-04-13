#include "Ray.h"

namespace Rendering
{
    Ray::Ray(const Utils::Vector3& origin, const Utils::Vector3& direction, const Utils::Color3& intensity)
        : m_origin(origin), m_direction(direction), m_intensity(intensity)
    {}

    Utils::Vector3 Ray::getPointAt(double t) const
    {
        return m_origin + t * m_direction;
    }
} // namespace Rendering