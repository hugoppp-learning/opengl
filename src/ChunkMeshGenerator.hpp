
#pragma once

#include "Chunk.hpp"
#include <glm/glm.hpp>
#include <vector>

struct Vertex {
    glm::vec3 pos;
    glm::vec3 normal;

    explicit Vertex(const glm::vec3 &pos, const glm::vec3 &normal) : pos(pos), normal(normal) {}
};

struct Triangle {
private:
    Vertex pos1;
    Vertex pos2;
    Vertex pos3;
public:
    Triangle(const glm::vec3 &normal, const glm::vec3 &pos1, const glm::vec3 &pos2, const glm::vec3 &pos3) :
        pos1(pos1, normal),
        pos2(pos2, normal),
        pos3(pos3, normal) {}

//    Triangle(Vertex pos1, Vertex pos2, Vertex pos3) :
//        pos1(pos1),
//        pos2(pos2),
//        pos3(pos3) {}
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
    std::vector<Triangle> tris;

    [[nodiscard]] const std::vector<Triangle> &GetData() const {
        return tris;
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
        auto pos = glm::vec3(x, y, z);

        if (y == Chunk::y_size - 1 || chunk.GetBlockType(x, y + 1, z) == BlockType::Air)
            AddTop(pos);
        if (y == 0 || chunk.GetBlockType(x, y - 1, z) == BlockType::Air)
            AddBottom(pos);
        if (z == 0 || chunk.GetBlockType(x, y, z - 1) == BlockType::Air)
            AddFront(pos);
        if (z == Chunk::z_size - 1 || chunk.GetBlockType(x, y, z + 1) == BlockType::Air)
            AddBack(pos);
        if (x == 0 || chunk.GetBlockType(x - 1, y, z) == BlockType::Air)
            AddLeft(pos);
        if (x == Chunk::x_size - 1 || chunk.GetBlockType(x + 1, y, z) == BlockType::Air)
            AddRight(pos);
    }

private:
    static constexpr auto up = glm::vec3(0, 1, 0);
    static constexpr auto down = glm::vec3(0, -1, 0);
    static constexpr auto back = glm::vec3(0, 0, 1);
    static constexpr auto front = glm::vec3(0, 0, -1);
    static constexpr auto right = glm::vec3(1, 0, 0);
    static constexpr auto left = glm::vec3(-1, 0, 0);

    inline void AddRight(const glm::vec3 &pos) {
        tris.emplace_back(right, b + pos, f + pos, c + pos);
        tris.emplace_back(right, g + pos, c + pos, f + pos);
    }

    inline void AddLeft(const glm::vec3 &pos) {
        tris.emplace_back(left, a + pos, d + pos, e + pos);
        tris.emplace_back(left, h + pos, e + pos, d + pos);
    }

    inline void AddBack(const glm::vec3 &pos) {
        tris.emplace_back(back, e + pos, h + pos, f + pos);
        tris.emplace_back(back, g + pos, f + pos, h + pos);
    }

    inline void AddFront(const glm::vec3 &pos) {
        tris.emplace_back(front, a + pos, b + pos, d + pos);
        tris.emplace_back(front, b + pos, c + pos, d + pos);
    }

    inline void AddBottom(const glm::vec3 &pos) {
        tris.emplace_back(down, e + pos, b + pos, a + pos);
        tris.emplace_back(down, f + pos, b + pos, e + pos);
    }

    inline void AddTop(const glm::vec3 &pos) {
        tris.emplace_back(up, d + pos, c + pos, h + pos);
        tris.emplace_back(up, g + pos, h + pos, c + pos);
    };
private:
};