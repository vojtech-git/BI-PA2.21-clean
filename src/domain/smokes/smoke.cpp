#include "domain/smokes/smoke.hpp"

Smoke::Smoke(SmokeId id, uint32_t x_position, uint32_t y_position, uint32_t size)
    : id_(id),
      x_position_(x_position),
      y_position_(y_position),
      size_(size) {}

void Smoke::Update(float dt) {
    smoke_timer_ -= dt;
}