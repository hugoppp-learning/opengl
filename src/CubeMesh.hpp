
#pragma once

#include "renderer/Mesh.hpp"
#include "Chunk.hpp"

struct CubeData {
    glm::vec3 Position;
    char Data;
};

class CubeMesh {
private:
    VertexBuffer vbo;
public:
    Mesh mesh;
    static const VertexBufferLayout vertexBufferLayout; = [] {
        return VertexBufferLayout().Push<float>(3).Push<char>(1);
    };

    CubeMesh(const Chunk chunk) : vbo(nullptr, sizeof(CubeData) * chunk.volume)
    , mesh(nullptr,chunk.volume,vertexBufferLayout){

        auto *gpuPointer = static_cast<CubeData *>(vbo.mapBuffer());

        auto t = new Array3D<CubeData, chunk.x_size, chunk.y_size, chunk.z_size>();

        for (int x = 0; x < chunk.x_size; ++x)
            for (int y = 0; y < chunk.y_size; ++y)
                for (int z = 0; z < chunk.z_size; ++z) {
                    new(gpuPointer) CubeData()
                    { .Position = glm::vec3(x, y, z), .Data = chunk.at(x, y, z) };
                }

    }


};
