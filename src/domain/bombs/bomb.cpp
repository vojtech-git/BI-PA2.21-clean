#include "domain/bombs/bomb.hpp"

Bomb::Bomb(BombId id, uint32_t x_position, uint32_t y_position, uint32_t explosion_size)
    : id_(id),
      x_position_(x_position),
      y_position_(y_position),
      explosion_size_(explosion_size) 
{
    detonation_timer_ = 4.0f;
}

BombId Bomb::GetId() const
{ 
    return id_; 
}

uint32_t Bomb::GetX() const
{ 
    return x_position_;
}

uint32_t Bomb::GetY() const
{ 
    return y_position_;
}

uint32_t Bomb::GetExplosionSize() const
{
    return explosion_size_;
}

float Bomb::GetDetonationTimer() const
{ 
    return detonation_timer_;
}

void Bomb::UpdateExplosion(float dt) {
    detonation_timer_ -= dt;
}