#include "../../include/camera/Camera.hpp"

#include <GL/glew.h>

#include <GL/gl.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace cge {

const CameraSettings CameraSettings::Default = {false, 0.01, 20.0,
                                                glm::radians(45.0)};

Camera::Camera()
    : __position{1, 1, 1}, __direction{0, 0, 1},
      __settings{false, glm::radians(45.0), 0.01, 20} {}

Camera::Camera(const glm::vec3 &position, const glm::vec3 &targetPoint,
               CameraSettings settings)
    : __position{position}, __direction{glm::normalize(targetPoint - position)},
      __settings(settings) {}

void Camera::setPosition(const glm::vec3 &position) { __position = position; }

glm::vec3 Camera::getPosition() const { return __position; }

void Camera::setTarget(const glm::vec3 &position) {
    __direction = glm::normalize(position - __position);
}

glm::vec3 Camera::getDirection() const { return __direction; }

void Camera::processZoom(float zoom) {
    __settings.angle -= zoom * 0.1;
    // __settings.angle = glm::clamp(__settings.angle, 20.0f, 45.0f);
    __settings.angle =
        glm::clamp(__settings.angle, glm::radians(20.0f), glm::radians(45.0f));
}

void Camera::changeSettings(CameraSettings settings) { __settings = settings; }

glm::mat4 Camera::getMatrix(const sf::RenderTarget &window) {
    glm::mat4 view =
        glm::lookAt(__position, __position + __direction, glm::vec3{0, 1, 0});
    glm::mat4 projection;
    if (!__settings.ortho) {
        projection = glm::perspective(
            __settings.angle,
            static_cast<glm::float32>(window.getSize().x) / window.getSize().y,
            __settings.near, __settings.far);
    } else {
        projection = glm::ortho(
            -0.001f * window.getSize().x, 0.001f * window.getSize().x,
            -0.001f * window.getSize().y, 0.001f * window.getSize().y,
            __settings.near, __settings.far);
    }

    return projection * view;
}

// void Camera::put(const sf::RenderTarget &window, Shader &program) {
//     auto matrix = getMatrix(window);
//     glUniformMatrix4fv(glGetUniformLocation(program.ID, "matCamera"), 1,
//                        GL_FALSE, glm::value_ptr(matrix));
//     auto error = glGetError();
//     if (error != GL_NO_ERROR) {
//         throw std::runtime_error(std::string{"OpenGL Error: "} +
//                                  std::to_string(error));
//     }
// }

} // namespace cge