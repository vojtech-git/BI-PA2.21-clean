#include "domain/walls/wall.hpp"

Wall::Wall(WallId id, Position position, WallType type)
    : id_(id),
      position_(position),
      type_(type) {}

WallId Wall::GetId() const {
    return id_;
}

Position Wall::GetPosition() const {
    return position_;
}

uint32_t Wall::GetX() const {
    return position_.x;
}

uint32_t Wall::GetY() const {
    return position_.y;
}

WallType Wall::GetType() const {
    return type_;
}