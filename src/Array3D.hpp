#pragma once

#include <array>
#include "myAssert.hpp"

template<class T, int x_size, int y_size, int z_size>
class Array3D {
public:
    [[nodiscard]] T &at(int x, int y, int z) {
        ASSERT_MSG(x < x_size, "x: " << x <<  " out of bounds");
        ASSERT_MSG(y < y_size, "y: " << y << " out of bounds");
        ASSERT_MSG(z < z_size, "y: " << z << " out of bounds");
        return m_array[x + y * x_size + z * x_size * y_size];
    }

    Array3D() : m_array() {}

private:
    std::array<T, x_size * y_size * z_size> m_array;

};



