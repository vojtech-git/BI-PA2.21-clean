#pragma once
#include <cstdint>
#include "domain/common/entity_id.hpp"
#include "domain/common/position.hpp"

enum class WallType {
    Soft,
    Hard
};

class Wall {
public:
    Wall(WallId id, Position position, WallType type);

    WallId GetId() const;
    Position GetPosition() const;
    uint32_t GetX() const;
    uint32_t GetY() const;
    WallType GetType() const;

private:
    WallId id_;
    Position position_;
    WallType type_;
};