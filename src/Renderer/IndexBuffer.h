#ifndef OPENGLTEST_INDEXBUFFER_H
#define OPENGLTEST_INDEXBUFFER_H

#include <glad/glad.h>

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


#endif //OPENGLTEST_INDEXBUFFER_H
