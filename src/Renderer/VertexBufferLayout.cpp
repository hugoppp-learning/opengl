#include "VertexBufferLayout.h"


template<>
void VertexBufferLayout::Push<float>(unsigned int count) {
    attributes.push_back({GL_FLOAT, count, GL_FALSE});
    stride += VertexBufferLayout::getSizeOfGLType(GL_FLOAT) * count;
}

template<>
void VertexBufferLayout::Push<int>(unsigned int count) {
    attributes.push_back({GL_INT, count, GL_FALSE});
    stride += VertexBufferLayout::getSizeOfGLType(GL_INT) * count;
}

template<>
void VertexBufferLayout::Push<unsigned int>(unsigned int count) {
    attributes.push_back({GL_UNSIGNED_INT, count, GL_FALSE});
    stride += VertexBufferLayout::getSizeOfGLType(GL_UNSIGNED_INT) * count;
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
        default:
            return 0;
    }
    ASSERT(false);
}
