#pragma once
#include <cstdint>
#include "domain/common/entity_id.hpp"
#include "domain/common/position.hpp"

class Ghost {
public:
    Ghost(GhostId id, Position position);

    GhostId GetId() const;
    Position GetPosition() const;
    uint32_t GetX() const;
    uint32_t GetY() const;

    void Update(float dt);
    bool CanMove() const;
    void ResetTimer();
    void Move(Position new_position);
    void Move(uint32_t new_x, uint32_t new_y);

private:
    GhostId id_;
    Position position_;
    float movement_timer_{0.0f};
    float move_interval_{0.0f};
};