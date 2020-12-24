#ifndef OPENGLTEST_RENDERER_H
#define OPENGLTEST_RENDERER_H

#include "VertexArray.h"
#include "Shader.h"


class Renderer {
public:
    void Draw(const VertexArray &va, const IndexBuffer &ib, const Shader &shader) const;

    void Clear() const;

    void DrawArrays(const VertexArray &va, const Shader &shader, unsigned int count) const;
};


#endif //OPENGLTEST_RENDERER_H
