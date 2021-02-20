#include "CubeMesh.hpp"

const CubeVertexBufferLayout CubeMesh::vertexBufferLayout = [] {
return VertexBufferLayout().Push<float>(3).Push<char>(1);
};
