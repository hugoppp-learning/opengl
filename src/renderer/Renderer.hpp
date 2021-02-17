#pragma once

#include "VertexArray.h"
#include "Shader.hpp"


class Renderer {
public:
    static void Draw(const VertexArray &vao, const IndexBuffer &ebo, const Shader &shader) ;

    static void Clear() ;

    static void DrawArrays(const VertexArray &vao, const Shader &shader, unsigned int count) ;
};


