#pragma once
#include <cstdint>
#include "domain/common/entity_id.hpp"

class Player;

enum class BonusType {
    Freeze,
    BombCooldown,
    FlameLength,
    Levitation,
    Health
};

class Bonus {
public:
    Bonus(BonusId id, uint32_t x_position, uint32_t y_position, BonusType type);

    BonusId GetId() const;
    uint32_t GetX() const;
    uint32_t GetY() const;
    BonusType GetType() const;

    void ApplyTo(Player &player) const;

private:
    BonusId id_;
    uint32_t x_position_;
    uint32_t y_position_;
    BonusType type_;
};