#pragma once

#include "Vector3.h"
#include "Ray.h"
#include "Texture.h"

namespace Rendering
{
    class Texture;

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

        // add texture
    };

    class Object
    {
    public:
        Object() = default;
        virtual ~Object() = default;

        virtual bool intersects(const Ray& ray, double t_min, double t_max, Intersection_record& record) const = 0;

        virtual Utils::Vector3 getNormalAt(const Utils::Point3& point, const Ray& ray, Intersection_record& record) const = 0;
    };

    class Sphere : public Object
    {
    public:
        Sphere(const Utils::Point3& center, double radius);

        virtual bool intersects(const Ray& ray, double t_min, double t_max, Intersection_record& record) const override;

        virtual Utils::Vector3 getNormalAt(const Utils::Point3& point, const Ray& ray, Intersection_record& record) const override;

    private:
        Utils::Point3 m_center;
        double m_radius;

        // add material
    };
}