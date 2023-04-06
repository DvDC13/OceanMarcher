#include "Texture.h"

#include "Object.h"

namespace Rendering
{
    UniformTexture::UniformTexture(const Utils::Color3& color, double diffuse, double specular)
        : m_color(color)
        , m_diffuse(diffuse)
        , m_specular(specular)
    {}

    bool UniformTexture::getTextureAt(const Rendering::Ray& ray_in,
        const Rendering::Intersection_record& record,
        Utils::Color3& color,
        Rendering::Ray& ray_out,
        double& diffuse,
        double& specular) const
    {
        auto disperced_direction = record.normal + Utils::normalize(Utils::randomInUnit());
        if (Utils::nearZero(disperced_direction)) disperced_direction = record.normal;
        ray_out = Ray(record.point, disperced_direction);
        color = m_color;
        diffuse = m_diffuse;
        specular = m_specular;
        return true;
    }

    MirrorTexture::MirrorTexture(const Utils::Color3& color)
        : m_color(color)
    {}

    bool MirrorTexture::getTextureAt(const Rendering::Ray& ray_in,
        const Rendering::Intersection_record& record,
        Utils::Color3& color,
        Rendering::Ray& ray_out,
        double& diffuse,
        double& specular) const
    {
        auto reflected = Utils::reflect(Utils::normalize(ray_in.getDirection()), record.normal);
        ray_out = Ray(record.point, reflected);
        color = m_color;
        return true;
    }
}