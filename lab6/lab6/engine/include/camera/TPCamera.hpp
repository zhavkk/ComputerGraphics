#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

#include "../objects/ObjectBase.hpp"
#include "Camera.hpp"

namespace cge {

class TPCamera : public Camera {
    friend class Scene;
    static constexpr float SENSITIVITY = 1.0f;
    static constexpr float MAX_PITCH = 89.0f;

   public:
    TPCamera(float radius = 1.0f, CameraSettings settings = CameraSettings::Default);
    void processMouse(float xoffset, float yoffset);

    void bind(ObjectBase* object_ptr);

    using Camera::changeSettings;
    using Camera::processZoom;

    glm::mat4 getMatrix(const sf::RenderTarget&) override;

   private:
    std::shared_ptr<ObjectBase> _m_object;
    float __radius;
};

}  // namespace cge
