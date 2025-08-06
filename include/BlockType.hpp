#pragma once
#include <cstdint>
#include <array>
#include "UV.hpp"
#include <stdexcept>

enum class FaceDirection {
    TOP,
    BOTTOM,
    LEFT,
    RIGHT,
    FRONT,
    BACK,
    COUNT
};

enum class BlockTypeId : uint8_t {
    DIRT,
    STONE,
    OAK_LOG,
    LEAVES,
    BEDROCK,
    GRASS,
    AIR,
    COUNT
};

struct BlockType {
    constexpr BlockType(std::array<UV, 6> faceUVs) : faceUVs(faceUVs) {}

    constexpr UV getUV(FaceDirection face) const {
        return faceUVs[static_cast<int>(face)];
    }

    std::array<UV, 6> faceUVs;
};

// Define all block types
constexpr BlockType DIRT_BLOCK     = BlockType(makeSameAll(2, 0));
constexpr BlockType STONE_BLOCK    = BlockType(makeSameAll(3, 0));
constexpr BlockType OAK_LOG_BLOCK  = BlockType({
    UV(0, 1), UV(1, 1), UV(1, 1), UV(1, 1), UV(1, 1), UV(1, 1)
});
constexpr BlockType LEAVES_BLOCK   = BlockType(makeSameAll(1, 2));
constexpr BlockType BEDROCK_BLOCK  = BlockType(makeSameAll(4, 0));
constexpr BlockType GRASS_BLOCK    = BlockType({
    UV(0, 0), UV(2, 0), UV(1, 0), UV(1, 0), UV(1, 0), UV(1, 0)
});
constexpr BlockType AIR_BLOCK      = BlockType(makeSameAll(0, 3)); // or unused

// Block registry
constexpr std::array<BlockType, static_cast<int>(BlockTypeId::COUNT)> blockTypes = {
    DIRT_BLOCK,
    STONE_BLOCK,
    OAK_LOG_BLOCK,
    LEAVES_BLOCK,
    BEDROCK_BLOCK,
    GRASS_BLOCK,
    AIR_BLOCK
};

constexpr const BlockType& getBlockType(BlockTypeId id) {
    int index = static_cast<int>(id);
    if (index < 0 || index >= static_cast<int>(BlockTypeId::COUNT)) {
        throw std::out_of_range("Invalid BlockTypeId index in getBlockType()");
    }
    return blockTypes[index];
}