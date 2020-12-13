#ifndef OPENGLTEST_VERTEXATTRIBUTES_H
#define OPENGLTEST_VERTEXATTRIBUTES_H

#include "myAssert.h"
#include <glad/glad.h>

class VertexAttributes {
public:
    unsigned int type;
    unsigned int count;
    GLboolean normalized;

    unsigned int GetSize(){
        return getSizeOfGLType(type);
    }

    static unsigned int getSizeOfGLType(unsigned int type){
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

};


#endif //OPENGLTEST_VERTEXATTRIBUTES_H
