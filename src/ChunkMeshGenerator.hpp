
#pragma once

#include "Chunk.hpp"
#include <glm/glm.hpp>
#include <vector>

struct Vertex {
private:
    glm::vec3 pos1;
    glm::vec3 pos2;
    glm::vec3 pos3;
public:
    Vertex(const glm::vec3 &pos1, const glm::vec3 &pos2, const glm::vec3 &pos3) :
        pos1(pos1),
        pos2(pos2),
        pos3(pos3)
        {}

};

class ChunkMesh {
private:
    static constexpr auto a = glm::vec3(0, 0, 0);
    static constexpr auto b = glm::vec3(1, 0, 0);
    static constexpr auto c = glm::vec3(1, 1, 0);
    static constexpr auto d = glm::vec3(0, 1, 0);

    static constexpr auto e = glm::vec3(0, 0, 1);
    static constexpr auto f = glm::vec3(1, 0, 1);
    static constexpr auto g = glm::vec3(1, 1, 1);
    static constexpr auto h = glm::vec3(0, 1, 1);

    /*                 h-------g
                      /|      /|
                     / |     / |
                    d--|----c  |
                    |  e----|--f
                    | /     | /
                    a-------b               */

public:
    std::vector<Vertex> vertecies;
    [[nodiscard]] const std::vector<Vertex>& GetData() const {
        return vertecies;
    }
    ChunkMesh(Chunk &chunk) {
        for (int x = 0; x < chunk.x_size; ++x)
            for (int y = 0; y < chunk.y_size; ++y)
                for (int z = 0; z < chunk.z_size; ++z) {
                    glm::vec3 curr(x, y, z);
                    BlockType type = chunk.GetBlockType(curr);
                    AddBlock(curr, type);
                }

    }

    void AddBlock(const glm::vec3 &pos, const BlockType &type) {
        // TOP
        vertecies.emplace_back(d + pos, c + pos, h + pos);
        vertecies.emplace_back(g + pos, h + pos, c + pos);
        // BOTTOM
        vertecies.emplace_back(e + pos, b + pos, a + pos);
        vertecies.emplace_back(f + pos, b + pos, e + pos);
        // FRONT
        vertecies.emplace_back(a + pos, b + pos, d + pos);
        vertecies.emplace_back(b + pos, c + pos, d + pos);
        // BACK
        vertecies.emplace_back(e + pos, h + pos, f + pos);
        vertecies.emplace_back(g + pos, f + pos, h + pos);
        //LEFT
        vertecies.emplace_back(a + pos, d + pos, e + pos);
        vertecies.emplace_back(h + pos, e + pos, d + pos);
        //RIGHT
        vertecies.emplace_back(b + pos, f + pos, c + pos);
        vertecies.emplace_back(g + pos, c + pos, f + pos);
    };
};