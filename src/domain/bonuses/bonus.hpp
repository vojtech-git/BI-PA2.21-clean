#pragma once
#include <cstddef>

enum class BonusType {
    Freeze,
    BomboCooldown,
    FlameLength,
    Levitation,
    Health
};

struct Bonus {
public:
    Bonus(size_t x_position, size_t y_position);

private:
    size_t x_position_;
    size_t y_position_;
    BonusType type_;
};