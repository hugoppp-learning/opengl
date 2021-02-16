#pragma once

#include <vector>
#include "Shader.h"

class VertexBufferLayout {
private:
    struct VertexAttributes {
    public:
        unsigned int m_type;
        unsigned int m_count;
        GLboolean m_normalized;

        [[nodiscard]] unsigned int GetSize() const {
            return VertexBufferLayout::getSizeOfGLType(m_type) * m_count;
        }
    };

    std::vector<VertexAttributes> m_attributes;
    unsigned int m_stride;

public:

    VertexBufferLayout() : m_stride(0) {}

    [[nodiscard]] std::vector<VertexAttributes> GetAttributes() const &{
        return m_attributes;
    }

    [[nodiscard]] unsigned int GetStride() const &{
        return m_stride;
    }

    template<typename T>
    VertexBufferLayout &Push(unsigned int count);

    static unsigned int getSizeOfGLType(unsigned int type);

};
