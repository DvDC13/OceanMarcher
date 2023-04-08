#pragma once

#include "Vector3.h"
#include "Ray.h"
#include "PhillipsSpectrum.h"

namespace Rendering
{
    struct Intersection_record
    {
        Utils::Point3 point;
        Utils::Vector3 normal;
        double t;

        bool front_face;

        inline void setFaceNormal(const Ray& ray, const Utils::Vector3& outward_normal)
        {
            front_face = Utils::dot(ray.getDirection(), outward_normal) < 0;
            normal = front_face ? outward_normal : -outward_normal;
        }
    };

    class Object
    {
    public:
        Object() = default;
        virtual ~Object() = default;

        virtual double getDistance(const Utils::Point3& point) const = 0;

        virtual Utils::Vector3 getNormalAt(const Utils::Point3& point, const Ray& ray, Intersection_record& record) const = 0;
    };

    class Sphere : public Object
    {
    public:
        Sphere(const Utils::Point3& center, double radius);

        virtual double getDistance(const Utils::Point3& point) const override;

        virtual Utils::Vector3 getNormalAt(const Utils::Point3& point, const Ray& ray, Intersection_record& record) const override;

    private:
        Utils::Point3 m_center;
        double m_radius;
    };

    class Water : public Object
    {
    public:
        Water() = default;

        virtual double getDistance(const Utils::Point3& point) const override;

        virtual Utils::Vector3 getNormalAt(const Utils::Point3& point, const Ray& ray, Intersection_record& record) const override;

    private:
        double bilinearInterpolation(double x, double y) const;
    };
}