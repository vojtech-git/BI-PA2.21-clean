#include "domain/ghosts/ghost.hpp"
#include "domain/common/game_constants.hpp"

Ghost::Ghost(GhostId id, Position position)
    : id_(id),
      position_(position),
      movement_timer_(domain::config::ghost::kMoveInterval),
      move_interval_(domain::config::ghost::kMoveInterval) {}

GhostId Ghost::GetId() const {
    return id_;
}

Position Ghost::GetPosition() const {
    return position_;
}

uint32_t Ghost::GetX() const {
    return position_.x;
}

uint32_t Ghost::GetY() const {
    return position_.y;
}

void Ghost::Update(float dt) {
    movement_timer_ -= dt;
}

bool Ghost::CanMove() const {
    return movement_timer_ <= 0.0f;
}

void Ghost::ResetTimer() {
    movement_timer_ = move_interval_;
}

void Ghost::Move(Position new_position) {
    position_ = new_position;
    ResetTimer();
}

void Ghost::Move(uint32_t new_x, uint32_t new_y) {
    Move(Position{new_x, new_y});
}