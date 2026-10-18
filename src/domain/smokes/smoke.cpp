#include "domain/smokes/smoke.hpp"
#include "domain/common/game_constants.hpp"

Smoke::Smoke(SmokeId id, Position position, uint32_t size)
    : id_(id),
      position_(position),
      smoke_timer_(domain::config::smoke::kSmokeDuration),
      size_(size) {}

SmokeId Smoke::GetId() const {
    return id_;
}

Position Smoke::GetPosition() const {
    return position_;
}

uint32_t Smoke::GetX() const {
    return position_.x;
}

uint32_t Smoke::GetY() const {
    return position_.y;
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