#pragma once

#include "Array3D.hpp"
#include "BlockType.hpp"

class Chunk {
public:
    static const int x_size = 16;
    static const int y_size = x_size;
    static const int z_size = x_size;
    Array3D<BlockType, x_size, y_size, z_size> data{};

    [[nodiscard]] const BlockType &GetBlockType(glm::ivec3 index) const {
        return data.at(index.x, index.y, index.z);
    }

    [[nodiscard]] const BlockType &GetBlockType(int x, int y, int z) const {
        return data.at(x, y, z);
    }

    void SetBlock(BlockType type, int x, int y, int z) {
        data.at(x, y, z) = type;
    }

    Chunk() : data() {
        for (int x = 0; x < x_size; ++x)
            for (int y = 0; y < x_size; ++y)
                for (int z = 0; z < x_size; ++z){
                    if (y < 10)
                        data.at(x,y,z) = BlockType::Earth;
                }

    }
};
