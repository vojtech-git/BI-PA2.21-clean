#pragma once
#include <cstdint>
#include "domain/common/entity_id.hpp"

class Smoke {
public:
    Smoke(SmokeId id, uint32_t x_position, uint32_t y_position, uint32_t size);

    SmokeId GetId() const;
    uint32_t GetX() const;
    uint32_t GetY() const;
    uint32_t GetSize() const;
    bool IsExpired() const;

    void Update(float dt);

private:
    SmokeId id_;
    uint32_t x_position_;
    uint32_t y_position_;
    float smoke_timer_{3.0f};
    uint32_t size_;
};