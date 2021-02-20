#pragma once

#include "Array3D.hpp"
#include "BlockType.hpp"

//template<int width, int height>
class Chunk {
private:
    static const int width = 16;
    static const int height = 16;
    Array3D<BlockType, width, height, width> m_array{};
public:

    Chunk() {
        for (int x = 0; x < x_size; ++x)
        for (int y = 0; y < y_size; ++y)
        for (int z = 0; z < z_size; ++z) {
            if (y < 40)
                m_array.at(x, y, z) = BlockType::Earth;
            else if (y < 45)
                m_array.at(x, y, z) = BlockType::Grass;
        }
    }

    static const int x_size = width;
    static const int y_size = height;
    static const int z_size = width;
    static const int volume = x_size * y_size * z_size;

    BlockType at(int x, int y, int z) {
        return m_array.at(x, y, z);
    }



};



