#include "../../include/shader/Shader.hpp"

#include <GL/glew.h>

#include <format>
#include <fstream>
#include <sstream>

namespace cge {

Shader::Shader(const std::string &vertexPath, const std::string &fragmentPath) {
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        // read file's buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        // close file handlers
        vShaderFile.close();
        fShaderFile.close();
        // convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    } catch (std::ifstream::failure e) {
        throw std::runtime_error("ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ");
    }
    const char *vShaderCode = vertexCode.c_str();
    const char *fShaderCode = fragmentCode.c_str();

    unsigned int vertex, fragment;
    int success;
    char infoLog[512];

    // vertex Shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, 0);
    glCompileShader(vertex);
    // print compile errors if any
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertex, 512, 0, infoLog);
        throw std::runtime_error(std::format(
            "ERROR::SHADER::VERTEX::COMPILATION_FAILED {}", infoLog));
    };

    // fragment Shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, 0);
    glCompileShader(fragment);
    // print compile errors if any
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragment, 512, 0, infoLog);
        throw std::runtime_error(std::format(
            "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED {}", infoLog));
    };

    // shader Program
    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    // print linking errors if any
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(ID, 512, 0, infoLog);
        throw std::runtime_error(
            std::format("ERROR::SHADER::PROGRAM::LINKING_FAILED {}", infoLog));
    }

    // delete the shaders as they're linked into our program now and no longer
    // necessary
    glDeleteShader(vertex);
    glDeleteShader(fragment);
    auto error = glGetError();
    if (error != GL_NO_ERROR) {
        throw std::runtime_error(std::string{"Shader Create Error: "} +
                                 std::to_string(error));
    }
}


void Shader::use() {
    glValidateProgram(ID);
    GLint validateStatus;
    glGetProgramiv(ID, GL_VALIDATE_STATUS, &validateStatus);
    if (validateStatus == GL_FALSE) {
        char infoLog[512];
        glGetProgramInfoLog(ID, 512, nullptr, infoLog);
        throw std::runtime_error(std::string{"Shader Validation Error: "} +
                                 infoLog);
    }

    glUseProgram(ID);
    auto error = glGetError();
    if (error != GL_NO_ERROR) {
        throw std::runtime_error(std::string{"Shader use Error: "} +
                                 std::to_string(error));
    }
}

Shader::~Shader() { glDeleteProgram(ID); }

void Shader::setTexture(const std::string &name, const Texture &tex) const {
    int64_t arr_ind[] = {
        GL_TEXTURE0,  GL_TEXTURE1,  GL_TEXTURE2,  GL_TEXTURE3,
        GL_TEXTURE4,  GL_TEXTURE5,  GL_TEXTURE6,  GL_TEXTURE7,
        GL_TEXTURE8,  GL_TEXTURE9,  GL_TEXTURE10, GL_TEXTURE11,
        GL_TEXTURE12, GL_TEXTURE13, GL_TEXTURE14, GL_TEXTURE15};

    auto tex_idx = arr_ind[tex.getIndex()];
    glActiveTexture(tex_idx);

    glBindTexture(GL_TEXTURE_2D, tex.ID);
    glUniform1i(glGetUniformLocation(this->ID, name.c_str()), tex.getIndex());

    
}

} // namespace cge
