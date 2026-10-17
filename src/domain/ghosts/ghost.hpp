#pragma once
#include <cstdint>
#include "domain/common/entity_id.hpp"

class Ghost {
public:
    Ghost(GhostId id, uint32_t x_position, uint32_t y_position);

    GhostId GetId() const { return id_; }
    uint32_t GetX() const { return x_position_; }
    uint32_t GetY() const { return y_position_; }

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