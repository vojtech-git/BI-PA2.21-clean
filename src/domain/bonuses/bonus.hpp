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
    Bonus(BonusId id, uint32_t x, uint32_t y, BonusType type);

    BonusId GetId() const { return id_; }
    uint32_t GetX() const { return x_; }
    uint32_t GetY() const { return y_; }
    BonusType GetType() const { return type_; }

    void ApplyTo(Player &player) const;

private:
    BonusId id_;
    uint32_t x_;
    uint32_t y_;
    BonusType type_;
};