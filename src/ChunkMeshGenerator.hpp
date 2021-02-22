
#pragma once

#include "Chunk.hpp"
#include <glm/glm.hpp>
#include <vector>


struct Vertex{
    glm::vec3 position;
    BlockType blockType;
};

class ChunkMesh {
private:
    std::vector<Vertex> vertecies;
    static

public:
    ChunkMesh(Chunk &chunk, glm::vec2 offset) {
        for (int x = 0; x < chunk.x_size; ++x) {
            for (int y = 0; y < chunk.y_size; ++y) {
                for (int z = 0; z < chunk.z_size; ++z) {



                }
            }
            chunk.data.at()
        }

    };
}