#include "Renderer.h"

void Renderer::Draw(const VertexArray &vao, const IndexBuffer &ebo, const Shader &shader) {
    shader.Bind();
    vao.Bind();
    glDrawElements(GL_TRIANGLES, ebo.GetCount(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::DrawArrays(const VertexArray &vao, const Shader &shader, unsigned int count) {
    shader.Bind();
    vao.Bind();
    glDrawArrays(GL_TRIANGLES, 0, count);
}

void Renderer::Clear() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
