#include "../../include/objects/Cube.hpp"

#include <GL/glew.h>

#include <GL/gl.h>

#include <glm/gtc/matrix_transform.hpp>

namespace cge {

inline sf::Image getColorImg(const glm::ivec3 &color) {
    sf::Image img;
    img.create(1, 1, {color.r, color.g, color.b});
    return img;
}

Cube::Cube(const std::string &name, const glm::ivec3 &color,
           const glm::f32 &len)
    : Cube(name, getColorImg(color), len) {}

Cube::Cube(const std::string &name, const sf::Image &img, const glm::f32 &len)
    : ObjectBase(name), __texture(img), __len(len), VAO(0), VBO(0) {
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    const float lend2 = len / 2;

    float verteces[] = {
        // координаты // текстура // нормаль
        // Задняя грань (-Z)
        -lend2, -lend2, -lend2, 1.0f, 0.0f, 0.0f, 0.0f,
        -1.0f, // нижний левый
        lend2, -lend2, -lend2, 0.0f, 0.0f, 0.0f, 0.0f,
        -1.0f, // нижний правый
        lend2, lend2, -lend2, 0.0f, 1.0f, 0.0f, 0.0f,
        -1.0f, // верхний правый
        lend2, lend2, -lend2, 0.0f, 1.0f, 0.0f, 0.0f,
        -1.0f, // верхний правый
        -lend2, lend2, -lend2, 1.0f, 1.0f, 0.0f, 0.0f,
        -1.0f, // верхний левый
        -lend2, -lend2, -lend2, 1.0f, 0.0f, 0.0f, 0.0f,
        -1.0f, // нижний левый

        // Передняя грань (+Z)
        -lend2, -lend2, lend2, 0.0f, 0.0f, 0.0f, 0.0f,
        1.0f, // нижний левый
        lend2, -lend2, lend2, 1.0f, 0.0f, 0.0f, 0.0f,
        1.0f, // нижний правый
        lend2, lend2, lend2, 1.0f, 1.0f, 0.0f, 0.0f,
        1.0f, // верхний правый
        lend2, lend2, lend2, 1.0f, 1.0f, 0.0f, 0.0f,
        1.0f, // верхний правый
        -lend2, lend2, lend2, 0.0f, 1.0f, 0.0f, 0.0f,
        1.0f, // верхний левый
        -lend2, -lend2, lend2, 0.0f, 0.0f, 0.0f, 0.0f,
        1.0f, // нижний левый

        // Левая грань (-X)
        -lend2, -lend2, -lend2, 0.0f, 0.0f, -1.0f, 0.0f,
        0.0f, // задний нижний
        -lend2, lend2, -lend2, 0.0f, 1.0f, -1.0f, 0.0f,
        0.0f, // задний верхний
        -lend2, lend2, lend2, 1.0f, 1.0f, -1.0f, 0.0f,
        0.0f, // передний верхний
        -lend2, lend2, lend2, 1.0f, 1.0f, -1.0f, 0.0f,
        0.0f, // передний верхний
        -lend2, -lend2, lend2, 1.0f, 0.0f, -1.0f, 0.0f,
        0.0f, // передний нижний
        -lend2, -lend2, -lend2, 0.0f, 0.0f, -1.0f, 0.0f,
        0.0f, // задний нижний

        // Правая грань (+X)
        lend2, -lend2, -lend2, 1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, // задний нижний
        lend2, lend2, -lend2, 1.0f, 1.0f, 1.0f, 0.0f,
        0.0f, // задний верхний
        lend2, lend2, lend2, 0.0f, 1.0f, 1.0f, 0.0f,
        0.0f, // передний верхнийcube
        lend2, lend2, lend2, 0.0f, 1.0f, 1.0f, 0.0f,
        0.0f, // передний верхний
        lend2, -lend2, lend2, 0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, // передний нижний
        lend2, -lend2, -lend2, 1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, // задний нижний

        // Нижняя грань (-Y)
        -lend2, -lend2, -lend2, 1.0f, 0.0f, 0.0f, -1.0f,
        0.0f, // задний левый
        lend2, -lend2, -lend2, 1.0f, 1.0f, 0.0f, -1.0f,
        0.0f, // задний правый
        lend2, -lend2, lend2, 0.0f, 1.0f, 0.0f, -1.0f,
        0.0f, // передний правый
        lend2, -lend2, lend2, 0.0f, 1.0f, 0.0f, -1.0f,
        0.0f, // передний правый
        -lend2, -lend2, lend2, 0.0f, 0.0f, 0.0f, -1.0f,
        0.0f, // передний левый
        -lend2, -lend2, -lend2, 1.0f, 0.0f, 0.0f, -1.0f,
        0.0f, // задний левый

        // Верхняя грань (+Y)
        -lend2, lend2, -lend2, 1.0f, 1.0f, 0.0f, 1.0f,
        0.0f, // задний левый
        lend2, lend2, -lend2, 1.0f, 0.0f, 0.0f, 1.0f,
        0.0f, // задний правый
        lend2, lend2, lend2, 0.0f, 0.0f, 0.0f, 1.0f,
        0.0f, // передний правый
        lend2, lend2, lend2, 0.0f, 0.0f, 0.0f, 1.0f,
        0.0f, // передний правый
        -lend2, lend2, lend2, 0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, // передний левый
        -lend2, lend2, -lend2, 1.0f, 1.0f, 0.0f, 1.0f,
        0.0f // задний левый
    };
    glBufferData(GL_ARRAY_BUFFER, sizeof(verteces), &verteces, GL_STATIC_DRAW);

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

    // glBindBuffer(GL_ARRAY_BUFFER, 0);
    // glBindVertexArray(0);
}

void Cube::draw(cge::Shader &shader) const {
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

Cube::~Cube() {
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
}

void Cube::setTexture(const sf::Image &img) {
    __texture.~Texture();
    Texture tmp(img);
    __texture = tmp;
    tmp.ID = 0;
}

std::pair<glm::vec3, glm::vec3> Cube::getBoundingBox() const {
    float halfLen = __len / 2.0f;

    std::vector<glm::vec3> localVertices = {
        {-halfLen, -halfLen, -halfLen}, {halfLen, -halfLen, -halfLen},
        {-halfLen, halfLen, -halfLen},  {halfLen, halfLen, -halfLen},
        {-halfLen, -halfLen, halfLen},  {halfLen, -halfLen, halfLen},
        {-halfLen, halfLen, halfLen},   {halfLen, halfLen, halfLen},
    };

    glm::vec3 minBounds = glm::vec3(std::numeric_limits<float>::max());
    glm::vec3 maxBounds = glm::vec3(std::numeric_limits<float>::lowest());

    for (const auto &vertex : localVertices) {
        glm::vec4 transformedVertex = __placement * glm::vec4(vertex, 1.0f);

        minBounds = glm::min(minBounds, glm::vec3(transformedVertex));
        maxBounds = glm::max(maxBounds, glm::vec3(transformedVertex));
    }

    return {minBounds, maxBounds};
}

} // namespace cge