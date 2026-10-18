#pragma once
#include <cstdint>
#include "domain/common/entity_id.hpp"

class Door {
public:
    Door(DoorId id, uint32_t x_position, uint32_t y_position);

    DoorId GetId() const;
    uint32_t GetX() const;
    uint32_t GetY() const;
    bool IsRevealed() const;

    void Reveal();

private:
    DoorId id_;
    uint32_t x_position_;
    uint32_t y_position_;
    bool revealed_{false};
};