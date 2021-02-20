#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include <CubeVertexAttribs.hpp>
#include <catch2/catch.hpp>

TEST_CASE("Attrib",""){
    auto attrib = CubeVertexAttribs();
    attrib.setBlockId(BlockType::LAST);
    attrib.setNormal(Direction::BACK);
    REQUIRE(attrib.getBlockType() == BlockType::LAST);
    REQUIRE(attrib.getDirection() == Direction::BACK);
    attrib.setNormal(Direction::FRONT);
    REQUIRE(attrib.getDirection() == Direction::FRONT);
    attrib.setBlockId(BlockType::Air);
    REQUIRE(attrib.getBlockType() == BlockType::Air);
    attrib.setNormal(Direction::UP);
    REQUIRE(attrib.getDirection() == Direction::UP);
}

