#pragma once

#include "Buffer.hpp"
#include "VertexBufferLayout.hpp"
#include <glad/glad.h>
#include <vector>

class VertexArray {
private:
    unsigned int m_renderer_id{};
public:
    VertexArray() {
        glGenVertexArrays(1, &m_renderer_id);
    }

    ~VertexArray() {
        glDeleteVertexArrays(1, &m_renderer_id);
    }

    /*
     * Binds buffer, creates and binds AttribPointers
     */
    void AddBuffer(const VertexBuffer &vb, const VertexBufferLayout &layout) const {
        Bind();
        vb.Bind();
        const auto attributes = layout.GetAttributes();
        unsigned int offset = 0;
        for (unsigned int i = 0; i < attributes.size(); i++) {
            const auto &attribute = attributes[i];
            glVertexAttribPointer(
                i, attribute.m_count, attribute.m_type, attribute.m_normalized, layout.GetStride(), (void *) offset);
            offset += attribute.GetSize();
            glEnableVertexAttribArray(i);
        }
    }

    void Bind() const {
        glBindVertexArray(m_renderer_id);
    }

    static void Unbind() {
        glBindVertexArray(0);
    }

};
