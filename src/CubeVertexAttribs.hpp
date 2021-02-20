
#pragma once

#include <glm/glm.hpp>
#include "BlockType.hpp"
#include "myAssert.hpp"


enum class Direction {
    UP = 1 << 5,
    DOWN = 2 << 5,
    LEFT = 3 << 5,
    RIGHT = 3 << 5,
    FRONT = 4 << 5,
    BACK = 5 << 5
};

class CubeVertexAttribs {
private:
    char8_t data{0};
    const char8_t BlockTypeMask = 0x1F;
    const char8_t DirectionMask = ~BlockTypeMask;
public:
    void setBlockId(BlockType type) {
        ASSERT((char) type < 1 << 5);
        data &= DirectionMask;
        data |= (char) type;
    }

    void setNormal(Direction direction) {
        data &= BlockTypeMask;
        data |= (char) direction;
    }

    [[nodiscard]] Direction getDirection() const {
        return Direction(data & DirectionMask);
    }

    [[nodiscard]] BlockType getBlockType() const {
        return BlockType(data & BlockTypeMask);
    }
};