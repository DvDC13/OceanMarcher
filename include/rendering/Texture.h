#pragma once

#include "Vector3.h"
#include "Ray.h"

namespace Rendering
{
    struct Intersection_data;

    class Texture
    {
    public:
        virtual ~Texture() = default;

        virtual bool getTextureAt(const Rendering::Ray& ray_in,
            const Rendering::Intersection_data& record,
            Utils::Color3& color,
            Rendering::Ray& ray_out,
            double& diffuse,
            double& specular) const = 0;
    };

    //class UniformTexture : public Texture
    //{
    //};
}