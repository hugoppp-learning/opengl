#ifndef OPENGLTEST_VERTEXBUFFERLAYOUT_H
#define OPENGLTEST_VERTEXBUFFERLAYOUT_H

#include <vector>
#include "Shader.h"

class VertexBufferLayout {
private:
    struct VertexAttributes {
    public:
        unsigned int type;
        unsigned int count;
        GLboolean normalized;

        unsigned int GetSize() const{
            return VertexBufferLayout::getSizeOfGLType(type) * count;
        }
    };
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

    template<typename T>
    void Push(unsigned int count);

    static unsigned int getSizeOfGLType(unsigned int type);
};


#endif //OPENGLTEST_VERTEXBUFFERLAYOUT_H
