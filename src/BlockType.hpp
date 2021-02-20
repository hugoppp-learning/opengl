#pragma once

enum class BlockType : unsigned char {
    Air = 0,
    Earth,
    Grass,
    Wood,
    LAST [[maybe_unused]] = (1 << 5) - 1
};
