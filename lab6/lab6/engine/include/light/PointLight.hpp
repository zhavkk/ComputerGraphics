#pragma once
#include <glm/glm.hpp>

namespace cge {

class PointLight {
  public:
    PointLight(const glm::vec3 &position,
               const glm::ivec3 &color = glm::ivec3(255))
        : __pos(position), __color(color) {}
    void setPosition(const glm::vec3 &position) { __pos = position; }
    glm::vec3 getPosition() const { return __pos; }
    void setColor(const glm::ivec3 &color) { __color = color; }
    glm::ivec3 getColor() const { return __color; }

  private:
    glm::vec3 __pos;
    glm::ivec3 __color;
};

} // namespace cge
