#pragma once
#include <cstdint>
#include "domain/common/entity_id.hpp"
#include "domain/common/position.hpp"

class Bomb {
public:
    Bomb(BombId id, Position position, uint32_t explosion_size);

    BombId GetId() const;
    Position GetPosition() const;
    uint32_t GetX() const;
    uint32_t GetY() const;
    uint32_t GetExplosionSize() const;
    float GetDetonationTimer() const;

    void UpdateDetonationTimer(float dt);

private:
    BombId id_;
    Position position_;
    float detonation_timer_;
    uint32_t explosion_size_;
};