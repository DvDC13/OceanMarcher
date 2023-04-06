#include "Object.h"

#include "Texture.h"

namespace Rendering
{
    Sphere::Sphere(const Utils::Vector3& center, double radius)
        : m_center(center)
        , m_radius(radius)
    {}

    double Sphere::getDistance(const Utils::Point3& point) const
    {
        return Utils::length(point - m_center) - m_radius;
    }

    Utils::Vector3 Sphere::getNormalAt(const Utils::Point3& point, const Ray& ray, Intersection_record& record) const
    {
        Utils::Vector3 outward_normal = Utils::normalize(point - m_center);
        record.setFaceNormal(ray, outward_normal);
        return record.normal;
    }
}