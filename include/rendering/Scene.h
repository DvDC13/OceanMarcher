#pragma once

#include <iostream>
#include <vector>
#include <memory>

#include "Camera.h"
#include "Object.h"

namespace Rendering
{
    class Scene : public Object
    {
    public:
        Scene(const std::vector<std::shared_ptr<Object>>& objects);

        void addObject(const std::shared_ptr<Object>& object);
        void clearObjects();

        inline const std::vector<std::shared_ptr<Object>>& getObjects() const { return m_objects; }
        inline const Camera& getCamera() const { return m_camera; }

        virtual bool intersects(const Ray& ray, double t_min, double t_max, Intersection_data& record) const override;
        virtual Utils::Vector3 getNormalAt(const Utils::Point3& point, const Ray& ray, Intersection_data& record) const override;

    private:
        std::vector<std::shared_ptr<Object>> m_objects;
        Camera m_camera;
    };
}