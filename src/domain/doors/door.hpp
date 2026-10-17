#pragma once
#include <cstdint>
#include "domain/common/entity_id.hpp"

class Door {
public:
    Door(DoorId id, uint32_t x_position, uint32_t y_position);

    DoorId GetId() const { return id_; }
    uint32_t GetX() const { return x_position_; }
    uint32_t GetY() const { return y_position_; }
    bool IsRevealed() const { return revealed_; }

    void Reveal();

private:
    DoorId id_;
    uint32_t x_position_;
    uint32_t y_position_;
    bool revealed_{false};
};