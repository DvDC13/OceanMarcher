#pragma once

#include <iostream>
#include <vector>
#include <memory>

#include "Camera.h"
#include "Object.h"

namespace Rendering
{
    class Scene
    {
    public:
        Scene(const std::vector<std::shared_ptr<Object>>& objects);

        void addObject(const std::shared_ptr<Object>& object);
        void clearObjects();

        inline const std::vector<std::shared_ptr<Object>>& getObjects() const { return m_objects; }
        inline const Camera& getCamera() const { return m_camera; }
        
    private:
        std::vector<std::shared_ptr<Object>> m_objects;
        Camera m_camera;
    };
}