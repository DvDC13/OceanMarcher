#include "Scene.h"

namespace Rendering
{
    Scene::Scene(const std::vector<std::shared_ptr<Object>>& objects)
        : m_objects(objects)
    {
        Utils::Vector3 look_from = Utils::Vector3(0, 0, -1);
        Utils::Vector3 look_at = Utils::Vector3(0, 0, 0);
        Utils::Vector3 up = Utils::Vector3(0, 1, 0);
        double vertical_fov = 90.0;
        double aspect_ratio = 1.0;
        m_camera = Rendering::Camera(look_from, look_at, up, vertical_fov, aspect_ratio);
    }

    void Scene::addObject(const std::shared_ptr<Object>& object)
    {
        m_objects.emplace_back(object);
    }

    void Scene::clearObjects()
    {
        m_objects.clear();
    }

    bool Scene::intersects(const Ray& ray, double t_min, double t_max, Intersection_data& record) const
    {
        Intersection_data tmp_record;
        bool hit = false;
        double closest_so_far = t_max;

        for (const auto& object : m_objects)
        {
            if (object->intersects(ray, t_min, closest_so_far, tmp_record))
            {
                hit = true;
                closest_so_far = tmp_record.t;
                record = tmp_record;
            }
        }

        return hit;
    }

    Utils::Vector3 Scene::getNormalAt(const Utils::Point3& point, const Ray& ray, Intersection_data& record) const
    {
        std::cerr << "Scene::getNormalAt() called!" << std::endl;
        return Utils::Vector3(0.0, 0.0, 0.0);
    }
}