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
        //double height = bilinearInterpolation(point.getX(), point.getZ());
        double height = 0.0;
        return point.getY() - height;
    }

    Utils::Vector3 Water::getNormalAt(const Utils::Point3& point, const Ray& ray, Intersection_record& record) const
    {
        double height = bilinearInterpolation(point.getX(), point.getZ());
        double heightX = bilinearInterpolation(point.getX() + 1, point.getZ());
        double heightZ = bilinearInterpolation(point.getX(), point.getZ() + 1);

        Utils::Vector3 vx = Utils::Vector3(1, heightX - height, 0);
        Utils::Vector3 vz = Utils::Vector3(0, heightZ - height, 1);
        Utils::Vector3 normal = Utils::cross(vx, vz);
        record.setFaceNormal(ray, normal);
        return record.normal;
    }

    double Water::bilinearInterpolation(double x, double y) const
    {
        int width = Settings::SCREEN_WIDTH - 1;
        int height = Settings::SCREEN_HEIGHT - 1;

        int xi0 = x - width * std::floor(x / width);
        int yi0 = y - height * std::floor(y / height);
        int xi1 = (xi0 + 1) - width * std::floor((xi0 + 1) / width);
        int yi1 = (yi0 + 1) - height * std::floor((yi0 + 1) / height);

        double sx = x - (double)std::floor(x);
        double sy = y - (double)std::floor(y);

        double topLeft = Ocean::heights[xi0 * (width + 1) + yi0];
        double topRight = Ocean::heights[xi1 * (width + 1) + yi0];
        double bottomLeft = Ocean::heights[xi0 * (width + 1) + yi1];
        double bottomRight = Ocean::heights[xi1 * (width + 1) + yi1];

        double top = (1 - sx) * topLeft + sx * topRight;
        double bottom = (1 - sx) * bottomLeft + sx * bottomRight;

        return (1 - sy) * top + sy * bottom;
    }
}