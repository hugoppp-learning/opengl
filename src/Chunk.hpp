#pragma once

#include "Array3D.hpp"
#include "BlockType.hpp"

class Chunk {
public:
    static const int x_size = 128;
    static const int y_size = x_size;
    static const int z_size = x_size;
    Array3D<BlockType, x_size, y_size, z_size> data{};

    [[nodiscard]] const BlockType &GetBlockType(glm::ivec3 index) const {
        return data(index);
    }

    [[nodiscard]] const BlockType &GetBlockType(int x, int y, int z) const {
        return data(x, y, z);
    }

    void SetBlock(BlockType type, glm::ivec3 index) {
        data(index) = type;
    }

    void SetBlock(BlockType type, int x, int y, int z) {
        data(x, y, z) = type;
    }

    Chunk() : data() {
        for (int x = 0; x < x_size; ++x)
            for (int y = 0; y < x_size; ++y)
                for (int z = 0; z < x_size; ++z) {
                    if (y - 5 < (x * z) / 512 + (sin((x * z) / 64)) * 5 + sin(x) + sin(z))
                        data(x, y, z) = BlockType::Earth;
                    else
                        data(x, y, z) = BlockType::Air;
                }

    }
};
