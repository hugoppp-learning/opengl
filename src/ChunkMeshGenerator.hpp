
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
        pos3(pos3) {}

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
         y          d--|----c  |
         |  z       |  e----|--f
         | /        | /     | /
         0----x     a-------b               */

public:
    std::vector<Vertex> vertecies;

    [[nodiscard]] const std::vector<Vertex> &GetData() const {
        return vertecies;
    }

    explicit ChunkMesh(Chunk &chunk) {
        for (int x = 0; x < chunk.x_size; ++x)
            for (int y = 0; y < chunk.y_size; ++y)
                for (int z = 0; z < chunk.z_size; ++z) {
                    BlockType type = chunk.GetBlockType(x, y, z);
                    if (type == BlockType::Air)
                        continue;
                    AddBlock(x, y, z, type, chunk);
                }

    }

    void AddBlock(int x, int y, int z, const BlockType &type, const Chunk &chunk) {
        bool isXmin = x == 0;
        bool isYmin = y == 0;
        bool isZmin = z == 0;
        bool isXmax = x == Chunk::x_size - 1;
        bool isYmax = y == Chunk::y_size - 1;
        bool isZmax = z == Chunk::z_size - 1;
        auto pos = glm::vec3(x, y, z);

        if (isYmax || chunk.GetBlockType(x, y + 1, z) == BlockType::Air)
            AddTop(pos);
        if (isYmin || chunk.GetBlockType(x, y - 1, z) == BlockType::Air)
            AddBottom(pos);
        if (isZmin || chunk.GetBlockType(x, y, z - 1) == BlockType::Air)
            AddFront(pos);
        if (isZmax || chunk.GetBlockType(x, y, z + 1) == BlockType::Air)
            AddBack(pos);
        if (isXmin || chunk.GetBlockType(x - 1, y, z) == BlockType::Air)
            AddLeft(pos);
        if (isXmax || chunk.GetBlockType(x + 1, y, z) == BlockType::Air)
            AddRight(pos);
    }

private:
    inline void AddRight(const glm::vec3 &pos) {
        vertecies.emplace_back(b + pos, f + pos, c + pos);
        vertecies.emplace_back(g + pos, c + pos, f + pos);
    }

    inline void AddLeft(const glm::vec3 &pos) {
        vertecies.emplace_back(a + pos, d + pos, e + pos);
        vertecies.emplace_back(h + pos, e + pos, d + pos);
    }

    inline void AddBack(const glm::vec3 &pos) {
        vertecies.emplace_back(e + pos, h + pos, f + pos);
        vertecies.emplace_back(g + pos, f + pos, h + pos);
    }

    inline void AddFront(const glm::vec3 &pos) {
        vertecies.emplace_back(a + pos, b + pos, d + pos);
        vertecies.emplace_back(b + pos, c + pos, d + pos);
    }

    inline void AddBottom(const glm::vec3 &pos) {
        vertecies.emplace_back(e + pos, b + pos, a + pos);
        vertecies.emplace_back(f + pos, b + pos, e + pos);
    }

    inline void AddTop(const glm::vec3 &pos) {
        vertecies.emplace_back(d + pos, c + pos, h + pos);
        vertecies.emplace_back(g + pos, h + pos, c + pos);
    };
private:
};