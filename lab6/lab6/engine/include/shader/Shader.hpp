#pragma once

#include <GL/glew.h>

#include "../texture/Texture.hpp"
#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>

namespace cge {

class Shader {
  public:
    // ID программы в OpenGL
    unsigned int ID;

    Shader() = default;

    // конструктор, считывающий шейдеры из файлов и компилирующий их
    Shader(const std::string &vertexPath, const std::string &fragmentPath);
    ~Shader();
    // активация шейдера
    void use();
    // установка текстуры в uniform шейдера (шейдер должен быть активен)
    void setTexture(const std::string &name, const Texture &tex) const;
    // установка переменной в uniform шейдера (шейдер должен быть активен)
    template <class T> void set(const std::string &name, T uniform) const {
        if constexpr (std::is_floating_point<T>()) {
            glUniform1f(glGetUniformLocation(ID, name.c_str()), uniform);
        } else {
            glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)uniform);
        }
    }
    // установка переменной в uniform шейдера (шейдер должен быть активен)
    template <int N, class T>
    void set(const std::string &name,
             const glm::vec<N, T, glm::packed_highp> &uniform) const {
        if constexpr (N == 4) {
            if constexpr (std::is_floating_point<T>()) {
                glUniform4f(glGetUniformLocation(ID, name.c_str()), uniform.x,
                            uniform.y, uniform.z, uniform.w);
            } else {
                glUniform4i(glGetUniformLocation(ID, name.c_str()), uniform.x,
                            uniform.y, uniform.z, uniform.w);
            }
        } else if constexpr (N == 3) {
            if constexpr (std::is_floating_point<T>()) {
                glUniform3f(glGetUniformLocation(ID, name.c_str()), uniform.x,
                            uniform.y, uniform.z);
            } else {
                glUniform3i(glGetUniformLocation(ID, name.c_str()), uniform.x,
                            uniform.y, uniform.z);
            }
        } else {
            if constexpr (std::is_floating_point<T>()) {
                glUniform2f(glGetUniformLocation(ID, name.c_str()), uniform.x,
                            uniform.y);
            } else {
                glUniform2i(glGetUniformLocation(ID, name.c_str()), uniform.x,
                            uniform.y);
            }
        }
    }

    template <int N, class T>
    void set(const std::string &name, const glm::mat<N, N, T> &uniform) {
        if constexpr (N == 4) {
            if constexpr (std::is_floating_point<T>()) {
                glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1,
                                   GL_FALSE, glm::value_ptr(uniform));
            } else {
                glUniformMatrix4iv(glGetUniformLocation(ID, name.c_str()), 1,
                                   GL_FALSE, glm::value_ptr(uniform));
            }
        } else if constexpr (N == 3) {
            if constexpr (std::is_floating_point<T>()) {
                glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1,
                                   GL_FALSE, glm::value_ptr(uniform));
            } else {
                glUniformMatrix3iv(glGetUniformLocation(ID, name.c_str()), 1,
                                   GL_FALSE, glm::value_ptr(uniform));
            }
        } else {
            if constexpr (std::is_floating_point<T>()) {
                glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1,
                                   GL_FALSE, glm::value_ptr(uniform));
            } else {
                glUniformMatrix2iv(glGetUniformLocation(ID, name.c_str()), 1,
                                   GL_FALSE, glm::value_ptr(uniform));
            }
        }
    }

    template <typename T>
    void setArr(const std::string &name,
                        const std::vector<T> &arr) const {
        GLuint location = glGetUniformLocation(ID, name.c_str());
        if constexpr (std::is_floating_point<T>::value) {
            glUniform1fv(location, arr.size(),
                         arr.data()); // для массива чисел с плавающей точкой
        } else if constexpr (std::is_integral<T>::value) {
            glUniform1iv(location, arr.size(),
                         arr.data()); // для массива целых чисел
        }
    }

    template <typename T>
    void setArr(const std::string &name,
                        const std::vector<glm::vec<3, T>> &arr) const {
        GLuint location = glGetUniformLocation(ID, name.c_str());
        if constexpr (std::is_floating_point<T>::value) {
            glUniform3fv(
                location, arr.size(),
                glm::value_ptr(arr.front())); // для массива vec3 с плавающей точкой
        } else if constexpr (std::is_integral<T>::value) {
            glUniform3iv(location, arr.size(),
                         glm::value_ptr(arr.front())); // для массива vec3 с целыми числами
        }
    }
};

} // namespace cge