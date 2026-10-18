#include "domain/walls/wall.hpp"

Wall::Wall(WallId id, uint32_t x_position, uint32_t y_position, WallType type)
    : id_(id),
      x_position_(x_position),
      y_position_(y_position),
      type_(type) {}

WallId Wall::GetId() const {
    return id_;
}

uint32_t Wall::GetX() const {
    return x_position_;
}

uint32_t Wall::GetY() const {
    return y_position_;
}

WallType Wall::GetType() const {
    return type_;
}