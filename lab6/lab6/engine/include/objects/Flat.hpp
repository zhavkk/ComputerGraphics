#pragma once

#include "../texture/Texture.hpp"
#include "ObjectBase.hpp"
#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>

namespace cge {

class Flat : public ObjectBase {
  public:
    Flat(const std::string &name, const glm::ivec3 &color,
         const glm::vec3& u, const glm::vec3& v);

    Flat(const std::string &name, const sf::Image &img,
         const glm::vec3& u, const glm::vec3& v);
    ~Flat();

    void setTexture(const sf::Image &tex);
    void draw(Shader &) const override;
    std::pair<glm::vec3, glm::vec3> getBoundingBox() const override;

  private:
    uint VAO, VBO;
    cge::Texture __texture;
    glm::vec3 __u, __v;
};

} // namespace cge