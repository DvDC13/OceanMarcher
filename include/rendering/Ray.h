#pragma once

#include "Vector3.h"

namespace Rendering
{
    class Ray
    {
    public:
        Ray() = default;
        Ray(const Utils::Vector3& origin, const Utils::Vector3& direction, const Utils::Color3& intensity);

        inline const Utils::Vector3& getOrigin() const { return m_origin; }
        inline const Utils::Vector3& getDirection() const { return m_direction; }
        inline const Utils::Color3& getIntensity() const { return m_intensity; }

        inline void setOrigin(const Utils::Vector3& origin) { m_origin = origin; }
        inline void setDirection(const Utils::Vector3& direction) { m_direction = direction; }
        inline void setIntensity(const Utils::Color3& intensity) { m_intensity = intensity; }
        
        Utils::Vector3 getPointAt(double t) const;

    private:
        Utils::Vector3 m_origin;
        Utils::Vector3 m_direction;
        Utils::Color3 m_intensity;
    };
} // namespace Rendering