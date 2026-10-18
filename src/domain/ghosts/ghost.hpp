#pragma once
#include <cstdint>
#include "domain/common/entity_id.hpp"

class Ghost {
public:
    Ghost(GhostId id, uint32_t x_position, uint32_t y_position);

    GhostId GetId() const;
    uint32_t GetX() const;
    uint32_t GetY() const;

    void Update(float dt);
    bool CanMove() const;
    void ResetTimer();
    void Move(uint32_t new_x_position, uint32_t new_y_position);

private:
    GhostId id_;
    uint32_t x_position_;
    uint32_t y_position_;
    float movement_timer_{1.0f};
    float move_interval_{1.0f};
};