#pragma once

#include "domain/common/position.hpp"
#include <cstdint>

class Map {
public:
    Map(uint32_t width, uint32_t height);
    uint32_t GetWidth() const;
    uint32_t GetHeight() const;
    bool IsInBounds(Position position) const;

private:
    uint32_t width_;
    uint32_t height_;
};