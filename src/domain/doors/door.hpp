#pragma once
#include <cstdint>
#include "domain/common/entity_id.hpp"
#include "domain/common/position.hpp"

class Door {
public:
    Door(DoorId id, Position position);

    DoorId GetId() const;
    Position GetPosition() const;
    uint32_t GetX() const;
    uint32_t GetY() const;
    bool IsRevealed() const;

    void Reveal();

private:
    DoorId id_;
    Position position_;
    bool revealed_{false};
};