#pragma once

#include "../texture/Texture.hpp"
#include "ObjectBase.hpp"
#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>

namespace cge {

class Cube : public ObjectBase {
  public:
    Cube(const std::string &name, const glm::ivec3 &color,
         const glm::f32 &len = 1.0f);

    Cube(const std::string &name, const sf::Image &img,
         const glm::f32 &len = 1.0f);
    ~Cube();

    void setTexture(const sf::Image &tex);
    void draw(Shader &) const override;
    std::pair<glm::vec3, glm::vec3> getBoundingBox() const override;

  private:
    uint VAO, VBO;
    cge::Texture __texture;
    glm::f32 __len;
};

} // namespace cge