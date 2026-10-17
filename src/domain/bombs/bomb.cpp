#include "domain/bombs/bomb.hpp"

Bomb::Bomb(BombId id, uint32_t x_position, uint32_t y_position, uint32_t explosion_size)
    : id_(id),
      x_position_(x_position),
      y_position_(y_position),
      explosion_size_(explosion_size) {}

void Bomb::UpdateExplosion(float dt) {
    detonation_timer_ -= dt;
}