#pragma once

#include <array>
#include "myAssert.hpp"
#include <glm/glm.hpp>

template<class T, int x_size, int y_size, int z_size>
class Array3D {
public:

    const T &operator()(const glm::ivec3 &index) const {
        return m_array[index.x + index.y * x_size + index.z * x_size * y_size];
    }

    T &operator()(const glm::ivec3 &index) {
        return m_array[index.x + index.y * x_size + index.z * x_size * y_size];
    }

    const T &operator()(int x, int y, int z) const {
        return m_array[x + y * x_size + z * x_size * y_size];
    }

    T &operator()(int x, int y, int z) {
        return m_array[x + y * x_size + z * x_size * y_size];
    }

    Array3D() {
        m_array = std::unique_ptr<T[]>(new T[x_size * y_size * z_size]);
    }

private:
    std::unique_ptr<T[]> m_array;
};



