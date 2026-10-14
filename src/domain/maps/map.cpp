#include "map.hpp"

Map::Map(size_t width, size_t height)
    : width_(width),
      height_(height) {}

size_t Map::GetWidth() const {
    return width_;
}

size_t Map::GetHeight() const {
    return height_;
}   