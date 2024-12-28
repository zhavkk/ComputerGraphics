#include "../../include/objects/Flat.hpp"

#include <array>

namespace cge {

inline sf::Image getColorImg(const glm::ivec3 &color) {
    sf::Image img;
    img.create(1, 1, {color.r, color.g, color.b});
    return img;
}

Flat::Flat(const std::string &name, const glm::ivec3 &color, const glm::vec3 &u,
           const glm::vec3 &v)
    : Flat(name, getColorImg(color), u, v) {}

Flat::Flat(const std::string &name, const sf::Image &img, const glm::vec3 &u,
           const glm::vec3 &v)
    : ObjectBase(name), VAO(), VBO(), __texture(img), __u(glm::normalize(u)),
      __v(glm::normalize(v)) {
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glm::vec3 normal = glm::normalize(glm::cross(__u, __v));

    glm::vec3 p0 = -(__u + __v) / 2.0f;

    std::vector<float> vertices = {
        // Позиция              // Текстура  // Нормаль
        p0.x,
        p0.y,
        p0.z,
        0.0f,
        0.0f,
        normal.x,
        normal.y,
        normal.z, //
        (p0 + __u).x,
        (p0 + __u).y,
        (p0 + __u).z,
        1.0f,
        0.0f,
        normal.x,
        normal.y,
        normal.z, //
        (p0 + __v).x,
        (p0 + __v).y,
        (p0 + __v).z,
        0.0f,
        1.0f,
        normal.x,
        normal.y,
        normal.z, //

        (p0 + __u).x,
        (p0 + __u).y,
        (p0 + __u).z,
        1.0f,
        0.0f,
        normal.x,
        normal.y,
        normal.z, //
        (p0 + __v).x,
        (p0 + __v).y,
        (p0 + __v).z,
        0.0f,
        1.0f,
        normal.x,
        normal.y,
        normal.z, //
        (p0 + __u + __v).x,
        (p0 + __u + __v).y,
        (p0 + __u + __v).z,
        1.0f,
        1.0f,
        normal.x,
        normal.y,
        normal.z};

    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(),
                 vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                          (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                          (void *)(5 * sizeof(float)));
    glEnableVertexAttribArray(2);

    auto error = glGetError();
    if (error != GL_NO_ERROR) {
        throw std::runtime_error(std::string{"OpenGL Error: "} +
                                 std::to_string(error));
    }
}

void Flat::draw(cge::Shader &shader) const {
    shader.use();
    shader.setTexture("myTexture", __texture);
    shader.set("modelMatrix", __placement);
    shader.set("is_glowing", is_glowing);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glDrawArrays(GL_TRIANGLES, 0, 36);

    auto error = glGetError();
    if (error != GL_NO_ERROR) {
        throw std::runtime_error(std::string{"OpenGL Error: "} +
                                 std::to_string(error));
    }

    // glBindBuffer(GL_ARRAY_BUFFER, 0);
    // glBindVertexArray(0);
}

Flat::~Flat() {
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
}

void Flat::setTexture(const sf::Image &img) {
    __texture.~Texture();
    Texture tmp(img);
    __texture = tmp;
    tmp.ID = 0;
}

std::pair<glm::vec3, glm::vec3> Flat::getBoundingBox() const {
    glm::vec3 min = glm::vec3(std::numeric_limits<float>::max());
    glm::vec3 max = glm::vec3(std::numeric_limits<float>::lowest());
    glm::vec3 origin = -(__u + __v) / 2.0f;

    // Вычисление локальных вершин на основе направляющих векторов
    std::array<glm::vec3, 4> vertices = {origin, origin + __u, origin + __v,
                                         origin + __u + __v};

    // Трансформируем вершины матрицей модели и обновляем границы AABB
    for (const auto &vertex : vertices) {
        glm::vec4 transformedVertex = __placement * glm::vec4(vertex, 1.0f);
        glm::vec3 pos(transformedVertex);

        min = glm::min(min, pos);
        max = glm::max(max, pos);
    }

    return {min, max};
}

} // namespace cge