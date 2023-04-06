#pragma once

#include "Vector3.h"
#include "Ray.h"

namespace Rendering
{
    struct Intersection_record;

    class Texture
    {
    public:
        virtual ~Texture() = default;

        virtual bool getTextureAt(const Rendering::Ray& ray_in,
            const Rendering::Intersection_record& record,
            Utils::Color3& color,
            Rendering::Ray& ray_out,
            double& diffuse,
            double& specular) const = 0;
    };

    class UniformTexture : public Texture
    {
    public:
        UniformTexture(const Utils::Color3& color, double diffuse, double specular);

        virtual bool getTextureAt(const Rendering::Ray& ray_in,
            const Rendering::Intersection_record& record,
            Utils::Color3& color,
            Rendering::Ray& ray_out,
            double& diffuse,
            double& specular) const override;

        inline const Utils::Color3& getColor() const { return m_color; }
        inline double getDiffuse() const { return m_diffuse; }
        inline double getSpecular() const { return m_specular; }

    private:
        Utils::Color3 m_color;
        double m_diffuse;
        double m_specular;
    };

    class MirrorTexture : public Texture
    {
    public:
        MirrorTexture(const Utils::Color3& color);

        virtual bool getTextureAt(const Rendering::Ray& ray_in,
            const Rendering::Intersection_record& record,
            Utils::Color3& color,
            Rendering::Ray& ray_out,
            double& diffuse,
            double& specular) const override;

        inline const Utils::Color3& getColor() const { return m_color; }

    private:
        Utils::Color3 m_color;
    };
}