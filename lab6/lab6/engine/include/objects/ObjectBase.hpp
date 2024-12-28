#pragma once

#include "../shader/Shader.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace cge {

class ObjectBase {
  public:
    std::string name;
    bool is_glowing;
    ObjectBase(const std::string &name)
        : name(name), __placement(glm::mat4(1)), is_glowing(false) {}
    glm::vec3 getPosition() const { return glm::vec3(__placement[3]); }
    void translate(const glm::vec3 &vec) {
        __placement = glm::translate(__placement, vec);
    }
    void rotate(glm::f32 angle, const glm::vec3 &vec) {
        __placement = glm::rotate(__placement, angle, vec);
    }
    void rotateX(glm::f32 angle) { rotate(angle, {1, 0, 0}); }
    void rotateY(glm::f32 angle) { rotate(angle, {0, 1, 0}); }
    void rotateZ(glm::f32 angle) { rotate(angle, {0, 0, 1}); }
    glm::vec3 getRotations() const {
        glm::mat3 rotationMatrix = glm::mat3(__placement);

        float angleY = -std::asin(rotationMatrix[2][0]);
        float angleX = 0.0f;
        float angleZ = 0.0f;

        if (std::cos(angleY) > 1e-6) { // Проверка на сингулярность
            // Угол поворота вокруг оси X (angleX)
            angleX = std::atan2(rotationMatrix[2][1], rotationMatrix[2][2]);
            // Угол поворота вокруг оси Z (angleZ)
            angleZ = std::atan2(rotationMatrix[1][0], rotationMatrix[0][0]);
        } else {
            // Обрабатываем случай, когда cos(angleY) близко к 0 (гимбаллок)
            angleX = 0.0f;
            angleZ = std::atan2(-rotationMatrix[0][1], rotationMatrix[1][1]);
        }

        return glm::vec3(angleX, angleY, angleZ);
    }
    void scale(const glm::vec3 &vec) {
        __placement = glm::scale(__placement, vec);
    }
    glm::vec3 getScale() const {
        // Извлекаем верхнюю левую 3x3 часть матрицы трансформации
        glm::mat3 rotationScaleMatrix = glm::mat3(__placement);

        // Длины векторов столбцов — это масштабирование
        float scaleX = glm::length(rotationScaleMatrix[0]); // Длина столбца X
        float scaleY = glm::length(rotationScaleMatrix[1]); // Длина столбца Y
        float scaleZ = glm::length(rotationScaleMatrix[2]); // Длина столбца Z

        return glm::vec3(scaleX, scaleY, scaleZ);
    }

    virtual void draw(Shader &) const = 0;
    virtual std::pair<glm::vec3, glm::vec3> getBoundingBox() const = 0;

  protected:
    glm::mat4 __placement;
};

} // namespace cge
