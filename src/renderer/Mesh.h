
#pragma once

#include <glm/glm.hpp>
#include <vector>
#include "Texture.h"
#include "VertexArray.h"
#include <optional>


struct Vertex {
    glm::vec3 Position;
    std::optional<glm::vec3> Normal;
    std::optional<glm::vec2> TexCoords;
    std::optional<glm::vec4> VertColors;

    Vertex(const glm::vec3 &position,
           const glm::vec3 &normal,
           const glm::vec2 &texCoords,
           const std::optional<glm::vec4> &vertColors = std::nullopt)
        : Position(position), Normal(normal), TexCoords(texCoords), VertColors(vertColors) {}
};

class Mesh {
public:
    Mesh(std::vector<Vertex> vertecies, std::vector<Texture> textures, std::vector<unsigned int> indicies);

    std::vector<Vertex> m_vertecies;
    std::vector<unsigned int> m_indicies;
    std::vector<Texture> m_textures;


    void Draw(Shader &shader);

private:
    VertexArray m_vao;
    VertexBuffer m_vbo;
    IndexBuffer m_ebo;

};


