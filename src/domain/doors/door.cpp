#include "domain/doors/door.hpp"

Door::Door(DoorId id, uint32_t x_position, uint32_t y_position)
    : id_(id),
      x_position_(x_position),
      y_position_(y_position) {}

void Door::Reveal() {
    revealed_ = true;
}