#include "bomb.hpp"

Bomb::Bomb(size_t x_position, size_t y_position, size_t explosion_size)
    : x_position_(x_position),
      y_position_(y_position),
      detonation_timer_(3.5f),
      explosion_size_(explosion_size) {}

void Bomb::UpdateExplosion(float dt) {
    detonation_timer_ -= dt;
}

size_t Bomb::GetX() const {
    return x_position_;
}

size_t Bomb::GetY() const {
    return y_position_;
}

size_t Bomb::GetExplosionSize() const {
    return explosion_size_;
}

float Bomb::GetDetonationTimer() const {
    return detonation_timer_;
}