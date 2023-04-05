#include "Object.h"

namespace Rendering
{
    Sphere::Sphere(const Utils::Vector3& center, double radius)
        : m_center(center)
        , m_radius(radius)
    {}

    bool Sphere::intersects(const Ray& ray, double t_min, double t_max, Intersection_data& record) const
    {
        Utils::Vector3 oc = ray.getOrigin() - m_center;
        double a = Utils::lengthSquared(ray.getDirection());
        double half_b = Utils::dot(oc, ray.getDirection());
        double c = Utils::lengthSquared(oc) - m_radius * m_radius;
        double delta = half_b * half_b - a * c;

        if (delta < 0) return false;

        double sqrtd = std::sqrt(delta);
        double root = (-half_b - sqrtd) / a;

        if (root < t_min || t_max < root)
        {
            root = (-half_b + sqrtd) / a;
            if (root < t_min || t_max < root)
                return false;
        }

        record.t = root;
        record.point = ray.getPointAt(record.t);
        record.normal = getNormalAt(record.point, ray, record);

        return true;
    }

    Utils::Vector3 Sphere::getNormalAt(const Utils::Point3& point, const Ray& ray, Intersection_data& record) const
    {
        Utils::Vector3 outward_normal = Utils::normalize(point - m_center);
        record.setFaceNormal(ray, outward_normal);
        return record.normal;
    }
}