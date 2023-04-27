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
        double height = 0.000048F * bilinearInterpolation(point.getX() * 5.0, point.getZ() * 5.0);

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

    // A COMPRENDRE
    double Water::bilinearInterpolation(double x, double z) const
    {
        double width = Settings::heightMapWidth;
        double height = Settings::heightMapHeight;

        double p_left = std::fmod((std::fmod(x, width) + width), width);
        double p_right = std::fmod((std::fmod(x + 1, width) + width), width);
        double p_top = std::fmod((std::fmod(z, height) + height), height);
        double p_bottom = std::fmod((std::fmod(z + 1, height) + height), height);

        int x1 = std::floor(p_left);
        int x2 = std::floor(p_right);
        int y1 = std::floor(p_top);
        int y2 = std::floor(p_bottom);

        double qTopLeft = Ocean::heights[y1 + x1 * (int)width];
        double qTopRight = Ocean::heights[y2 + x1 * (int)width];
        double qBottomLeft = Ocean::heights[y1 + x2 * (int)width];
        double qBottomRight = Ocean::heights[y2 + x2 * (int)width];

        double xRatio = x - std::floor(x);
        double yRatio = z - std::floor(z);

        double qTop = qTopLeft * (1 - xRatio) + qTopRight * xRatio;
        double qBottom = qBottomLeft * (1 - xRatio) + qBottomRight * xRatio;

        return qTop * (1 - yRatio) + qBottom * yRatio;
    }
}