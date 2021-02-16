
#pragma once

#include <glm/glm.hpp>
#include <utility>
#include <vector>
#include "Texture.h"
#include "VertexArray.h"
#include "Renderer.h"
#include <optional>
#include <variant>


struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;

    Vertex(const glm::vec3 &position,
           const glm::vec3 &normal
    )
        : Position(position), Normal(normal) {}
};

class Mesh {
public:

    Mesh(void *vertecies,
         int vertecies_count,
         const VertexBufferLayout &layout,
         std::optional<std::vector<unsigned int>> indicies = std::nullopt)
        : m_vertecies(vertecies),
          m_vertecies_count(vertecies_count),
          m_indicies(std::move(indicies)),
          m_vao(),
          m_vbo(m_vertecies, m_vertecies_count * layout.GetStride()),
          m_ebo() {

        if (m_indicies.has_value()) {
            m_ebo = IndexBuffer(&m_indicies.value()[0], m_indicies.value().size());
        }

        m_vao.AddBuffer(m_vbo, layout);
    }

    int m_vertecies_count;
    void *m_vertecies;
    std::optional<std::vector<unsigned int>> m_indicies;

    void Draw(Shader &shader) const {
        if (m_ebo.has_value())
            Renderer::Draw(m_vao, m_ebo.value(), shader);
        else
            Renderer::DrawArrays(m_vao, shader, m_vertecies_count);
    }

private:
    VertexArray m_vao;
    VertexBuffer m_vbo;
    std::optional<IndexBuffer> m_ebo;
};
