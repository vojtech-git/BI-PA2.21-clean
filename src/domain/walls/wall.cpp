#include "wall.hpp"

Wall::Wall(size_t x_position, size_t y_position, WallType type)
    : x_position_(x_position),
      y_position_(y_position),
      type_(type) {}

size_t Wall::GetX() const {
    return x_position_;
}

size_t Wall::GetY() const {
    return y_position_;
}

WallType Wall::GetType() const {
    return type_;
}