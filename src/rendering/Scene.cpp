#include "Scene.h"

namespace Rendering
{
    Scene::Scene(const std::vector<std::shared_ptr<Object>>& objects)
        : m_objects(objects)
    {
        Utils::Vector3 look_from = Utils::Vector3(0, 0.75, -0.5);
        Utils::Vector3 look_at = Utils::Vector3(0.0, 0.2, 0.8);
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
}