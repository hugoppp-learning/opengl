#ifndef OPENGLTEST_VERTEXBUFFER_H
#define OPENGLTEST_VERTEXBUFFER_H

#include <glad/glad.h>

class VertexBuffer  {
private:
    unsigned int renderer_id;
    unsigned int size;

public:

    VertexBuffer(const void *data, unsigned int size) : size(size) { // NOLINT(cppcoreguidelines-pro-type-member-init)
        glGenBuffers(1, &renderer_id);
        glBindBuffer(GL_ARRAY_BUFFER, renderer_id);
        glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)(size), data, GL_STATIC_DRAW);
    }

    ~VertexBuffer() {
        glDeleteBuffers(1, &renderer_id);
    }

    void Bind() const {
        glBindBuffer(GL_ARRAY_BUFFER, renderer_id);
    }

    void Unbind() const { // NOLINT(readability-convert-member-functions-to-static)
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    unsigned int GetSize() const{
        return size;
    };

};


#endif //OPENGLTEST_VERTEXBUFFER_H
