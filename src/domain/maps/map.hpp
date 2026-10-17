#pragma once
#include <cstdint>

class Map {
public:
    Map(uint32_t width, uint32_t height);

    uint32_t GetWidth() const { return width_; }
    uint32_t GetHeight() const { return height_; }

    bool IsInBounds(long long x, long long y) const;
    bool IsInBounds(uint32_t x, uint32_t y) const;

private:
    uint32_t width_;
    uint32_t height_;
};