#pragma once

#include "Ray.h"
#include "Scene.h"

namespace Rendering
{
    const double precision = 300.0;

    bool objectIntersects(const Rendering::Ray& ray, const auto& object, Rendering::Intersection_record& record, double closest_so_far);

    bool worldIntersects(const Rendering::Ray& ray, const Rendering::Scene& world, Rendering::Intersection_record& record, double closest_so_far);

} // namespace Rendering