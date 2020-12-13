#ifndef OPENGLTEST_VERTEXARRAY_H
#define OPENGLTEST_VERTEXARRAY_H

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include <glad/glad.h>

class VertexArray {
private:

public:
    unsigned int renderer_id;

    VertexArray() { // NOLINT(cppcoreguidelines-pro-type-member-init)
        glGenVertexArrays(1, &renderer_id);
    }

    ~VertexArray() {
        glDeleteVertexArrays(1, &renderer_id);
    }

    void AddBuffer(const VertexBuffer &vb, const VertexBufferLayout &layout) const {
        Bind();
        vb.Bind();
        const auto attributes = layout.GetAttributes();
        unsigned int offset = 0;
        for (unsigned int i = 0; i < attributes.size(); i++) {
            const auto &attribute = attributes[i];
            glEnableVertexAttribArray(i);
            glVertexAttribPointer(
                i, attribute.count, attribute.type, attribute.normalized, layout.GetStride(), (void *) offset);
            offset += attribute.count * VertexAttributes::getSizeOfGLType(attribute.type);
        }
    }

    void Bind() const {
        glBindVertexArray(renderer_id);
    }

    void Unbind() const { // NOLINT(readability-convert-member-functions-to-static)
        glBindVertexArray(0);
    }

};


#endif //OPENGLTEST_VERTEXARRAY_H
