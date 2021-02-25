#include "VertexBufferLayout.hpp"
#include "myAssert.hpp"


template<>
VertexBufferLayout &VertexBufferLayout::Push<float>(unsigned int count) {
    m_attributes.push_back({GL_FLOAT, count, GL_FALSE});
    m_stride += VertexBufferLayout::getSizeOfGLType(GL_FLOAT) * count;
    return *this;
}

template<>
VertexBufferLayout &VertexBufferLayout::Push<int>(unsigned int count) {
    m_attributes.push_back({GL_INT, count, GL_FALSE});
    m_stride += VertexBufferLayout::getSizeOfGLType(GL_INT) * count;
    return *this;
}

template<>
VertexBufferLayout &VertexBufferLayout::Push<unsigned int>(unsigned int count) {
    m_attributes.push_back({GL_UNSIGNED_INT, count, GL_FALSE});
    m_stride += VertexBufferLayout::getSizeOfGLType(GL_UNSIGNED_INT) * count;
    return *this;
}

template<>
VertexBufferLayout &VertexBufferLayout::Push<unsigned char>(unsigned int count) {
    m_attributes.push_back({GL_UNSIGNED_BYTE, count, GL_FALSE});
    m_stride += VertexBufferLayout::getSizeOfGLType(GL_UNSIGNED_BYTE) * count;
    return *this;
}

template<>
VertexBufferLayout &VertexBufferLayout::Push<char>(unsigned int count) {
    m_attributes.push_back({GL_BYTE, count, GL_FALSE});
    m_stride += VertexBufferLayout::getSizeOfGLType(GL_BYTE) * count;
    return *this;
}

unsigned int VertexBufferLayout::getSizeOfGLType(unsigned int type) {
    switch (type) {
        case GL_FLOAT:
            return sizeof(GLfloat);
        case GL_UNSIGNED_INT:
            return sizeof(GLuint);
        case GL_INT:
            return sizeof(GLint);
        case GL_BYTE:
            return sizeof(GLbyte);
        case GL_UNSIGNED_BYTE:
            return sizeof(GLubyte);
        default:
            ASSERT_MSG(false, "size of gl type not definied");
    }
}
