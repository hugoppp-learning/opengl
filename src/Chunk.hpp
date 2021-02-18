
#pragma once

#include <array>
#include "Array3D.hpp"

enum class BlockType : unsigned char {
    Air = 0,
    Earth,
    Grass,
    Wood
};

class Chunk {
public:
    static constexpr int x_size = 12;
    static constexpr int y_size = 12;
    static constexpr int z_size = x_size;
    static constexpr int volume = x_size * y_size * z_size;
private:
    Array3D<BlockType, x_size, y_size, z_size> m_array;
public:
    BlockType &at(int x, int y, int z) {
        return m_array.at(x, y, z);
    }

};



