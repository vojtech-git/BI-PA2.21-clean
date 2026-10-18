#include "domain/smokes/smoke.hpp"

Smoke::Smoke(SmokeId id, uint32_t x_position, uint32_t y_position, uint32_t size)
    : id_(id),
      x_position_(x_position),
      y_position_(y_position),
      size_(size) {}

SmokeId Smoke::GetId() const {
    return id_;
}

uint32_t Smoke::GetX() const {
    return x_position_;
}

uint32_t Smoke::GetY() const {
    return y_position_;
}

uint32_t Smoke::GetSize() const {
    return size_;
}

bool Smoke::IsExpired() const {
    return smoke_timer_ <= 0.0f;
}

void Smoke::Update(float dt) {
    smoke_timer_ -= dt;
}