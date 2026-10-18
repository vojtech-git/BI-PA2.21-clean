#include "domain/doors/door.hpp"

Door::Door(DoorId id, Position position)
    : id_(id),
      position_(position) {}

DoorId Door::GetId() const {
    return id_;
}

Position Door::GetPosition() const {
    return position_;
}

uint32_t Door::GetX() const {
    return position_.x;
}

uint32_t Door::GetY() const {
    return position_.y;
}

bool Door::IsRevealed() const {
    return revealed_;
}

void Door::Reveal() {
    revealed_ = true;
}