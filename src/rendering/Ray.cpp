#include "Ray.h"

namespace Rendering
{
    Ray::Ray(const Utils::Vector3& origin, const Utils::Vector3& direction)
        : m_origin(origin), m_direction(direction)
    {}

    Utils::Vector3 Ray::getPointAt(double t) const
    {
        return m_origin + t * m_direction;
    }
} // namespace Rendering