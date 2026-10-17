#pragma once
#include <cstdint>
#include "domain/common/entity_id.hpp"

class Bomb {
public:
    Bomb(BombId id, uint32_t x_position, uint32_t y_position, uint32_t explosion_size);

    BombId GetId() const { return id_; }
    uint32_t GetX() const { return x_position_; }
    uint32_t GetY() const { return y_position_; }
    uint32_t GetExplosionSize() const { return explosion_size_; }
    float GetDetonationTimer() const { return detonation_timer_; }

    void UpdateExplosion(float dt);

private:
    BombId id_;
    uint32_t x_position_;
    uint32_t y_position_;
    float detonation_timer_{3.5f};
    uint32_t explosion_size_;
};