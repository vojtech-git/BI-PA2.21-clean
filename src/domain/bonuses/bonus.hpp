#pragma once
#include <cstdint>
#include "domain/common/entity_id.hpp"
#include "domain/common/position.hpp"

enum class BonusType {
    Freeze,
    BombCooldown,
    FlameLength,
    Levitation,
    Health
};

class Bonus {
public:
    Bonus(BonusId id, Position position, BonusType type);

    BonusId GetId() const;
    Position GetPosition() const;
    uint32_t GetX() const;
    uint32_t GetY() const;
    BonusType GetType() const;

private:
    BonusId id_;
    Position position_;
    BonusType type_;
};