#pragma once

#include <glm/glm.hpp>

namespace cge {

class DirectLight {
  public:
    DirectLight(const glm::vec3 &direction,
                const glm::ivec3 &color = glm::ivec3(255))
        : __color(color), __direction(direction) {}
    void setDirection(const glm::vec3 &direction) { __direction = direction; }
    glm::vec3 getDirection() const { return __direction; }
    void setColor(const glm::ivec3 &color) { __color = color; }
    glm::ivec3 getColor() const { return __color; }

  private:
    glm::ivec3 __color;
    glm::vec3 __direction;
};

} // namespace cge