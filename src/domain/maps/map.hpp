#pragma once
#include <cstddef>

class Map {
public:
    Map(size_t width, size_t height);

    size_t GetWidth() const;
    size_t GetHeight() const;

private:
    size_t width_;
    size_t height_;
};