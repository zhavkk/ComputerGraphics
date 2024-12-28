#include "../../include/camera/FPCamera.hpp"

#include <glm/gtc/matrix_transform.hpp>

namespace cge {

FPCamera::FPCamera(CameraSettings settings) { __settings = settings; }

void FPCamera::bind(ObjectBase* object_ptr) { _m_object.reset(object_ptr); }

glm::mat4 FPCamera::getMatrix(const sf::RenderTarget& rt) {
    __position = _m_object->getPosition();
    return Camera::getMatrix(rt);
}

void FPCamera::processMouse(float xoffset, float yoffset) {
    xoffset *= SENSITIVITY;
    yoffset *= SENSITIVITY;

    glm::mat4 rotation_y = glm::rotate(glm::mat4(1.0f), glm::radians(xoffset),
                                       glm::vec3(0.0f, 1.0f, 0.0f));
    glm::vec3 right =
        glm::normalize(glm::cross(__direction, glm::vec3(0.0f, 1.0f, 0.0f)));
    glm::mat4 rotation_x =
        glm::rotate(glm::mat4(1.0f), glm::radians(yoffset), right);

    glm::vec4 new_direction =
        rotation_x * rotation_y * glm::vec4(__direction, 1.0f);

    __direction = glm::normalize(glm::vec3(new_direction));
}

}  // namespace cge
