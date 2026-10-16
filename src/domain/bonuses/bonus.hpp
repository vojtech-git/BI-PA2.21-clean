#pragma once
#include <cstddef>

enum class BonusType {
    Freeze,
    BombCooldown,
    FlameLength,
    Levitation,
    Health
};

class Bonus {
public:
    Bonus(size_t x, size_t y, BonusType type);

    size_t GetX() const;
    size_t GetY() const;
    BonusType GetType() const;

private:
    size_t x_;
    size_t y_;
    BonusType type_;
};