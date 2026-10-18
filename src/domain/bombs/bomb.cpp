#include "domain/bombs/bomb.hpp"
#include "domain/common/game_constants.hpp"

Bomb::Bomb(BombId id, Position position, uint32_t explosion_size)
    : id_(id),
      position_(position),
      detonation_timer_(domain::config::bomb::kDetonationDuration),
      explosion_size_(explosion_size) {}

BombId Bomb::GetId() const {
    return id_;
}

Position Bomb::GetPosition() const {
    return position_;
}

uint32_t Bomb::GetX() const {
    return position_.x;
}

uint32_t Bomb::GetY() const {
    return position_.y;
}

uint32_t Bomb::GetExplosionSize() const {
    return explosion_size_;
}

float Bomb::GetDetonationTimer() const {
    return detonation_timer_;
}

void Bomb::UpdateDetonationTimer(float dt) {
    detonation_timer_ -= dt;
}