#pragma once

#include "../shader/Shader.hpp"
#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>

namespace cge {

class Scene;

struct CameraSettings {
    static const CameraSettings Default;

    bool ortho;

    glm::float32 near;  // near flat
    glm::float32 far;   // far flat
    glm::float32 angle; // angle of view
};

class Camera {
    friend class Scene;

  public:
    Camera();
    // конструктор камеры с позицией камеры и позицией цели
    Camera(const glm::vec3 &position, const glm::vec3 &targetPoint,
           CameraSettings = CameraSettings::Default);

    void setPosition(const glm::vec3 &position);
    glm::vec3 getPosition() const;
    void setTarget(const glm::vec3 &position);
    glm::vec3 getDirection() const;

    void processZoom(float zoom);

    void changeSettings(CameraSettings);

    // получение матрицы камеры для использования в вычислениях
    // matrix = projection * view
    virtual glm::mat4 getMatrix(const sf::RenderTarget &window);

    // // set uniform "matCamera"
    // // for using of this in shaders
    // virtual void put(const sf::RenderTarget &, Shader &program);

  protected:
    glm::vec3 __position;
    glm::vec3 __direction;
    CameraSettings __settings;
};

} // namespace cge