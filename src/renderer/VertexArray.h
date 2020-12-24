#ifndef OPENGLTEST_VERTEXARRAY_H
#define OPENGLTEST_VERTEXARRAY_H

#include "Buffer.h"
#include "VertexBufferLayout.h"
#include <glad/glad.h>

class VertexArray {
private:
    unsigned int m_renderer_id;
public:
    VertexArray() { // NOLINT(cppcoreguidelines-pro-type-member-init)
        glGenVertexArrays(1, &m_renderer_id);
    }

    ~VertexArray() {
        glDeleteVertexArrays(1, &m_renderer_id);
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
                i, attribute.m_count, attribute.m_type, attribute.m_normalized, layout.GetStride(), (void *) offset);
            offset += attribute.GetSize();
        }
    }

    void Bind() const {
        glBindVertexArray(m_renderer_id);
    }

    void Unbind() const { // NOLINT(readability-convert-member-functions-to-static)
        glBindVertexArray(0);
    }

};


#endif //OPENGLTEST_VERTEXARRAY_H
