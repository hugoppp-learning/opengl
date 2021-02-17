// copied from https://learnopengl.com/Getting-started/Shaders
#include "Shader.hpp"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/vec3.hpp>


Shader::Shader(const char *vertexPath, const char *fragmentPath) {
    // 1. retrieve the vertex/fragment source code from m_filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    // ensure if stream objects can throw exceptions:
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        // open filejs
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
    }
    catch (std::ifstream::failure &e) {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
    }
    const char *vShaderCode = vertexCode.c_str();
    const char *fShaderCode = fragmentCode.c_str();
    // 2. compile shaders
    unsigned int vertex, fragment;
    // vertex shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, nullptr);
    glCompileShader(vertex);
    checkCompileErrors(vertex, "VERTEX");
    // fragment Shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, nullptr);
    glCompileShader(fragment);
    checkCompileErrors(fragment, "FRAGMENT");
    // shader Program
    m_renderer_id = glCreateProgram();
    glAttachShader(m_renderer_id, vertex);
    glAttachShader(m_renderer_id, fragment);
    glLinkProgram(m_renderer_id);
    checkCompileErrors(m_renderer_id, "PROGRAM");
    // delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::Bind() const {
    glUseProgram(m_renderer_id);
}

void Shader::SetUniformMatrix4f(const std::string &name, const float *value) {
    glUniformMatrix4fv(GetUniformLocation(name),1, GL_FALSE, value);
}

void Shader::SetUniform1b(const std::string &name, bool value) {
    glUniform1i(GetUniformLocation(name), (int) value);
}

void Shader::SetUniform1i(const std::string &name, int value) {
    glUniform1i(GetUniformLocation(name), value);
}

void Shader::SetUniform1f(const std::string &name, float value) {
    glUniform1f(GetUniformLocation(name), value);
}

void Shader::SetUniform4f(const std::string &name, const glm::vec4 &vec4) {
    glUniform4f(GetUniformLocation(name), vec4.x, vec4.y, vec4.z, vec4.z);
}

void Shader::SetUniform3f(const std::string &name, const glm::vec3 &vec3) {
    glUniform3f(GetUniformLocation(name), vec3.x, vec3.y, vec3.z);
}

void Shader::SetUniform3f(const std::string &name, float v0, float v1, float v2) {
    glUniform3f(GetUniformLocation(name), v0, v1, v2);
}

void Shader::SetUniform4f(const std::string &name, float v0, float v1, float v2, float v3) {
    glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
}

void Shader::checkCompileErrors(unsigned int shader, const std::string &type) {
    int success;
    char infoLog[1024];
    if (type != "PROGRAM") {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog
                      << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    } else {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog
                      << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
}

void Shader::Unbind() {
    glUseProgram(0);
}

int Shader::GetUniformLocation(const std::string &name) {
    if (m_uniform_location.find(name) != m_uniform_location.end())
        return m_uniform_location[name];

    int location = glGetUniformLocation(m_renderer_id, name.c_str());
    if (location < 0)
        std::cout << "WARNING::UNIFORM_LOCATION_DOES_NOT_EXIST: " << name << std::endl;
    else
        m_uniform_location[name] = location;
    return location;
}
