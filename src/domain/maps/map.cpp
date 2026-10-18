#include "domain/maps/map.hpp"

Map::Map(uint32_t width, uint32_t height)
    : width_(width),
      height_(height) {}

uint32_t Map::GetWidth() const {
    return width_;
}

uint32_t Map::GetHeight() const {
    return height_;
}

bool Map::IsInBounds(Position position) const {
    return position.x < width_ && position.y < height_;
}