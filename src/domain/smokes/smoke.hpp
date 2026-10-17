#pragma once
#include <cstdint>
#include "domain/common/entity_id.hpp"

class Smoke {
public:
    Smoke(SmokeId id, uint32_t x_position, uint32_t y_position, uint32_t size);

    SmokeId GetId() const { return id_; }
    uint32_t GetX() const { return x_position_; }
    uint32_t GetY() const { return y_position_; }
    uint32_t GetSize() const { return size_; }
    bool IsExpired() const { return smoke_timer_ <= 0.0f; }

    void Update(float dt);

private:
    SmokeId id_;
    uint32_t x_position_;
    uint32_t y_position_;
    float smoke_timer_{3.0f};
    uint32_t size_;
};