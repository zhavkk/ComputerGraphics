#include "../../include/camera/TPCamera.hpp"

#include <glm/gtc/matrix_transform.hpp>

namespace cge {

TPCamera::TPCamera(float radius, CameraSettings settings)
    : __radius(radius) {
    __settings = settings;
}

void TPCamera::bind(ObjectBase *object_ptr) { _m_object.reset(object_ptr); }

void TPCamera::processMouse(float xoffset, float yoffset) {
    xoffset *= SENSITIVITY;
    yoffset *= SENSITIVITY;

    xoffset = -xoffset;
    yoffset = -yoffset;

    // Вычисляем текущий угол наклона (pitch) относительно оси Y
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    float current_pitch = glm::degrees(glm::asin(glm::dot(__direction, up)));

    // Проверяем, чтобы новый угол не превышал пределы
    float new_pitch = current_pitch + yoffset;
    if (new_pitch > MAX_PITCH) {
        yoffset = MAX_PITCH - current_pitch;
    } else if (new_pitch < -MAX_PITCH) {
        yoffset = -MAX_PITCH - current_pitch;
    }

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

glm::mat4 TPCamera::getMatrix(const sf::RenderTarget &rt) {
    __position = _m_object->getPosition();
    __position -= __radius * __direction;
    auto result = Camera::getMatrix(rt);
    __position += __radius * __direction;
    return result;
}

} // namespace cge
