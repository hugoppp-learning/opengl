// copied from https://learnopengl.com/Getting-started/Shaders
#pragma once
#include <glad/glad.h>
#include <string>
#include <unordered_map>

class Shader {
private:
    unsigned int m_renderer_id;
    std::unordered_map<std::string, int> m_uniform_location;
public:

    Shader(const char *vertexPath, const char *fragmentPath);

    void Bind() const;

    void SetUniform1b(const std::string &name, bool value);

    void SetUniform1i(const std::string &name, int value);

    void SetUniform1f(const std::string &name, float value);

    void SetUniform4f(const std::string &name, float v0, float v1, float v2, float v3);

    int GetUniformLocation(const std::string &name);

    static void Unbind();

    static void checkCompileErrors(unsigned int shader, const std::string &type);

    void SetUniformMatrix4v(const std::string &name, const float *value);
};
