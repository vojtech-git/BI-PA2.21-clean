#include "smoke.hpp"

Smoke::Smoke(size_t x_position, size_t y_position, size_t size)
    : x_position_(x_position),
      y_position_(y_position),
      smoke_timer_(3.0f),
      size_(size) {}

void Smoke::Update(float dt) {
    smoke_timer_ -= dt;
}

bool Smoke::IsExpired() const {
    return smoke_timer_ <= 0.0f;
}

size_t Smoke::GetX() const {
    return x_position_;
}

size_t Smoke::GetY() const {
    return y_position_;
}