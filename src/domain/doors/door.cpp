#include "door.hpp"

Door::Door(size_t x_position, size_t y_position)
    : x_position_(x_position),
      y_position_(y_position),
      revealed_(false) {}

void Door::Reveal() {
    revealed_ = true;
}

bool Door::IsRevealed() const {
    return revealed_;
}

size_t Door::GetX() const {
    return x_position_;
}

size_t Door::GetY() const {
    return y_position_;
}