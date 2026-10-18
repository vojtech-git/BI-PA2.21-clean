#pragma once
#include <cstdint>
#include "domain/common/entity_id.hpp"

class Bomb {
public:
    Bomb(BombId id, uint32_t x_position, uint32_t y_position, uint32_t explosion_size);

    BombId GetId() const;
    uint32_t GetX() const;
    uint32_t GetY() const;
    uint32_t GetExplosionSize() const;
    float GetDetonationTimer() const;

    void UpdateExplosion(float dt);

private:
    BombId id_;
    uint32_t x_position_;
    uint32_t y_position_;
    float detonation_timer_;
    uint32_t explosion_size_;
};

