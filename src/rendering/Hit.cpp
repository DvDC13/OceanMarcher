#include "Hit.h"

namespace Rendering
{
    bool objectIntersects(const Rendering::Ray &ray, const auto &object, Rendering::Intersection_record &record, double closest_so_far)
    {
        double distanceFromOrigin = 0.0;
        Utils::Point3 hitPoint = ray.getPointAt(distanceFromOrigin);
        for (double p = 0; p < precision; p++)
        {
            hitPoint = ray.getPointAt(distanceFromOrigin);
            double distanceFromObject = object->getDistance(hitPoint);

            if (std::abs(distanceFromObject) < 0.001)
            {
                if (distanceFromOrigin >= closest_so_far)
                {
                    return false;
                }

                record.point = hitPoint;
                record.t = distanceFromOrigin;
                object->getNormalAt(hitPoint, ray, record);

                return true;
            }

            if (distanceFromOrigin > 1000.0)
            {
                return false;
            }

            distanceFromOrigin += distanceFromObject;
        }

        return false;
    }

    bool worldIntersects(const Rendering::Ray &ray, const Rendering::Scene &world, Rendering::Intersection_record &record, double closest_so_far)
    {
        bool hit_anything = false;
        Rendering::Intersection_record tmp_record;

        for (const auto &object : world.getObjects())
        {
            if (objectIntersects(ray, object, tmp_record, closest_so_far))
            {
                hit_anything = true;
                closest_so_far = record.t;
                record = tmp_record;
            }
        }

        return hit_anything;
    }
}