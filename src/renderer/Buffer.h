#ifndef OPENGLTEST_BUFFER_H
#define OPENGLTEST_BUFFER_H

#include <glad/glad.h>

class VertexBuffer  {
private:
    unsigned int m_renderer_id;
    unsigned int m_size;

public:

    VertexBuffer(const void *data, unsigned int size) : m_size(size) { // NOLINT(cppcoreguidelines-pro-type-member-init)
        glGenBuffers(1, &m_renderer_id);
        glBindBuffer(GL_ARRAY_BUFFER, m_renderer_id);
        glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)(size), data, GL_STATIC_DRAW);
    }

    ~VertexBuffer() {
        glDeleteBuffers(1, &m_renderer_id);
    }

    void Bind() const {
        glBindBuffer(GL_ARRAY_BUFFER, m_renderer_id);
    }

    void Unbind() const { // NOLINT(readability-convert-member-functions-to-static)
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    unsigned int GetSize() const{
        return m_size;
    };

};


class IndexBuffer {
private:
    unsigned int renderer_id;
    unsigned int count;

public:
    void Bind() const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderer_id);
    }

    IndexBuffer(const unsigned int *data, unsigned int count) // NOLINT(cppcoreguidelines-pro-type-member-init)
        : count(count) {
        glGenBuffers(1, &renderer_id);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderer_id);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), data, GL_STATIC_DRAW);
    }

    ~IndexBuffer() {
        glDeleteBuffers(1, &renderer_id);
    }

    void Unbind() { // NOLINT(readability-convert-member-functions-to-static)
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    unsigned int GetCount() const {
        return count;
    }
};

#endif //OPENGLTEST_BUFFER_H
