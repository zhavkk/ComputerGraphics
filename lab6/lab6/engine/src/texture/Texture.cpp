#include "../../include/texture/Texture.hpp"

namespace cge {

sf::Image img_from_color(const glm::ivec3 &color) {
    sf::Image img;
    img.create(1, 1, {color.r, color.g, color.b});
    return img;
}

Texture::Texture(const glm::ivec3 &color, const uint index)
    : Texture(img_from_color(color), index) {}

Texture::Texture(const sf::Image &image, const uint index)
    : _m_index(index), _m_size(image.getSize().x, image.getSize().y) {

    assert(index < 16);

    glGenTextures(1, &ID);

    int64_t arr_ind[] = {
        GL_TEXTURE0,  GL_TEXTURE1,  GL_TEXTURE2,  GL_TEXTURE3,
        GL_TEXTURE4,  GL_TEXTURE5,  GL_TEXTURE6,  GL_TEXTURE7,
        GL_TEXTURE8,  GL_TEXTURE9,  GL_TEXTURE10, GL_TEXTURE11,
        GL_TEXTURE12, GL_TEXTURE13, GL_TEXTURE14, GL_TEXTURE15};

    auto tex_idx = arr_ind[_m_index];

    glActiveTexture(tex_idx);

    glBindTexture(GL_TEXTURE_2D, ID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    const auto [width, height] = image.getSize();

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA,
                 GL_UNSIGNED_BYTE, image.getPixelsPtr());
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);

    auto error = glGetError();
    if (error != GL_NO_ERROR) {
        throw std::runtime_error(std::string{"OpenGL Error: "} +
                                 std::to_string(error));
    }
}

Texture::~Texture() { glDeleteTextures(1, &ID); }

uint Texture::getIndex() const { return _m_index; }
void Texture::setIndex(const uint &index) { _m_index = index; }

glm::uvec2 Texture::getSize() const { return _m_size; }

} // namespace cge