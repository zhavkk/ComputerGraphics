#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

#include "../objects/ObjectBase.hpp"
#include "Camera.hpp"

namespace cge {

class FPCamera : public Camera {
    friend class Scene;
    static constexpr float SENSITIVITY = 1.0f;
   public:
    FPCamera(CameraSettings settings = CameraSettings::Default);
    void processMouse(float xoffset, float yoffset);

    void bind(ObjectBase* object_ptr);

    using Camera::changeSettings;
    using Camera::processZoom;

    glm::mat4 getMatrix(const sf::RenderTarget&) override;

   private:
    std::shared_ptr<ObjectBase> _m_object;
};

}  // namespace cge
