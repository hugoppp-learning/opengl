
#include "Mesh.h"
#include "Renderer.h"

#include <utility>

Mesh::Mesh(std::vector<Vertex> vertecies , std::vector<Texture> textures, std::vector<unsigned int> indicies)
    : m_vertecies(std::move(vertecies)),
      m_indicies(std::move(indicies)),
      m_textures(std::move(textures)),
      m_vao(),
      m_vbo(&m_vertecies, m_vertecies.size() * sizeof(float)),
      m_ebo(&m_indicies[0], m_indicies.size()) {

    assert(textures.size() <= 1 && "Only one texture supported for now");

    auto layout = VertexBufferLayout();
    layout.Push<float>(3 + 3 + 3 + 2);
    m_vao.AddBuffer(m_vbo, layout);
}

void Mesh::Draw(Shader &shader) {
    Renderer::Draw(m_vao, m_ebo, shader);
}

