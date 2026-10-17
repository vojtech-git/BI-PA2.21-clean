#include "domain/ghosts/ghost.hpp"

Ghost::Ghost(GhostId id, uint32_t x_position, uint32_t y_position)
    : id_(id),
      x_position_(x_position),
      y_position_(y_position) {}

void Ghost::Update(float dt) {
    movement_timer_ -= dt;
}

bool Ghost::CanMove() const {
    return movement_timer_ <= 0.0f;
}

void Ghost::ResetTimer() {
    movement_timer_ = move_interval_;
}

void Ghost::Move(uint32_t new_x_position, uint32_t new_y_position) {
    x_position_ = new_x_position;
    y_position_ = new_y_position;
    ResetTimer();
}