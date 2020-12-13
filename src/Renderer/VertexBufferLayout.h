#ifndef OPENGLTEST_VERTEXBUFFERLAYOUT_H
#define OPENGLTEST_VERTEXBUFFERLAYOUT_H

#include <vector>
#include "Shader.h"
#include "VertexAttributes.h"

class VertexBufferLayout {
private:
    std::vector<VertexAttributes> attributes;
    unsigned int stride;

public:

    VertexBufferLayout() : stride(0) {}

    std::vector<VertexAttributes> GetAttributes() const &{
        return attributes;
    }

    unsigned int GetStride() const &{
        return stride;
    }

    void Push(GLuint attribType, unsigned int count) {
        attributes.push_back({attribType, count, GL_FALSE});
        stride += VertexAttributes::getSizeOfGLType(attribType) * count;
    }


};


#endif //OPENGLTEST_VERTEXBUFFERLAYOUT_H
