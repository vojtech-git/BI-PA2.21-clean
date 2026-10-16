#include "ghost.hpp"

Ghost::Ghost(size_t x_position, size_t y_position)
    : x_position_(x_position),
      y_position_(y_position),
      movement_timer_(1.0f),
      move_interval_(1.0f) {}

void Ghost::Update(float dt) {
    movement_timer_ -= dt;
}

bool Ghost::CanMove() const {
    return movement_timer_ <= 0.0f;
}

void Ghost::ResetTimer() {
    movement_timer_ = move_interval_;
}

void Ghost::Move(size_t new_x_position, size_t new_y_position) {
    x_position_ = new_x_position;
    y_position_ = new_y_position;
    ResetTimer();
}