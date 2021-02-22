
#pragma once
#include "Array3D.hpp"
#include "BlockType.hpp"

class Chunk {
public:
    static const int x_size = 16;
    static const int y_size = x_size;
    static const int z_size = x_size;
    Array3D <BlockType, x_size, y_size, z_size> data{};
};



