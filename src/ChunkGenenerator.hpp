
#pragma once

#define xyz x, y, z

class ChunkGenenerator {
public:

    static void generate(Chunk &chunk) {
        for (int x = 0; x < chunk.x_size; ++x)
        for (int y = 0; y < chunk.y_size; ++y)
        for (int z = 0; z < chunk.z_size; ++z) {
            if (y < 40)
                chunk.at(xyz) = BlockType::Earth;
            else if (y < 45)
                chunk.at(xyz) = BlockType::Grass;
        }
    }


private:


};



