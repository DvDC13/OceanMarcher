#pragma once

#include "Vector3.h"

namespace Rendering
{
    class Ray
    {
    public:
        Ray(const Utils::Vector3& origin, const Utils::Vector3& direction);

        inline const Utils::Vector3& getOrigin() const { return m_origin; }
        inline const Utils::Vector3& getDirection() const { return m_direction; }

        Utils::Vector3 getPointAt(double t) const;
    private:
        Utils::Vector3 m_origin;
        Utils::Vector3 m_direction;
    };
} // namespace Rendering