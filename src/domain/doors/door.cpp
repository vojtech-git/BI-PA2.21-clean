#include "domain/doors/door.hpp"

Door::Door(DoorId id, uint32_t x_position, uint32_t y_position)
    : id_(id),
      x_position_(x_position),
      y_position_(y_position) {}

DoorId Door::GetId() const {
    return id_;
}

uint32_t Door::GetX() const {
    return x_position_;
}

uint32_t Door::GetY() const {
    return y_position_;
}

bool Door::IsRevealed() const {
    return revealed_;
}

void Door::Reveal() {
    revealed_ = true;
}