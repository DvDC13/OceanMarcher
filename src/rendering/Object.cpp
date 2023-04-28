#include "Object.h"

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

    double Water::getDistance(const Utils::Point3& point) const
    {
        double height = 0.000048F * bilinearInterpolation(point.getX() * 6.0, point.getZ() * 6.0);

        return point.getY() - height;
    }

    Utils::Vector3 Water::getNormalAt(const Utils::Point3& point, const Ray& ray, Intersection_record& record) const
    {
        double epsilon = 0.001;

        Utils::Vector3 dx = Utils::Vector3(epsilon, 0, 0);
        Utils::Vector3 dy = Utils::Vector3(0, epsilon, 0);
        Utils::Vector3 dz = Utils::Vector3(0, 0, epsilon);

        double x = getDistance(point + dx) - getDistance(point - dx);
        double y = getDistance(point + dy) - getDistance(point - dy);
        double z = getDistance(point + dz) - getDistance(point - dz);

        Utils::Vector3 normal = Utils::normalize(Utils::Vector3(x, y, z));
        record.setFaceNormal(ray, normal);
        return record.normal;
    }

    double mod(double x, double y)
    {
        return x - y * std::floor(x / y);
    }

    double lerp(double x, double y, float a)
    {
        return (1.f - a) * x + a * y;
    }

    double Water::bilinearInterpolation(double x, double y) const
    {
        int width = Settings::heightMapWidth;
        int height = Settings::heightMapHeight;

        int xi1 = mod(x, width - 1);
        int yi1 = mod(y, height - 1);
        int xi2 = mod(x + 1, width - 1);
        int yi2 = mod(y + 1, height - 1);

        double topLeft = Ocean::heights[yi1 + xi1 * width];
        double topRight = Ocean::heights[yi1 + xi2 * width];
        double bottomLeft = Ocean::heights[yi2 + xi1 * width];
        double bottomRight = Ocean::heights[yi2 + xi2 * width];

        double xf = x - std::floor(x);
        double top = lerp(topLeft, topRight, xf);
        double bottom = lerp(bottomLeft, bottomRight, xf);

        double yf = y - std::floor(y);
        return lerp(top, bottom, yf);
    }
}