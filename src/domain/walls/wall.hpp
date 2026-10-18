#pragma once
#include <cstdint>
#include "domain/common/entity_id.hpp"

enum class WallType {
    Soft,
    Hard
};

class Wall {
public:
    Wall(WallId id, uint32_t x_position, uint32_t y_position, WallType type);

    WallId GetId() const;
    uint32_t GetX() const;
    uint32_t GetY() const;
    WallType GetType() const;

private:
    WallId id_;
    uint32_t x_position_;
    uint32_t y_position_;
    WallType type_;
};