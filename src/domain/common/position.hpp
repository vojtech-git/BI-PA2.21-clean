#pragma once
#include <cstdint>

struct Position {
    uint32_t x{0};
    uint32_t y{0};

    constexpr bool operator==(const Position &other) const {
        return x == other.x && y == other.y;
    }

    constexpr bool operator!=(const Position &other) const {
        return !(*this == other);
    }
};