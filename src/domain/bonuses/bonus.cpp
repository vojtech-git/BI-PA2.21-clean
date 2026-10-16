#include "bonus.hpp"

Bonus::Bonus(size_t x, size_t y, BonusType type)
    : x_(x), y_(y), type_(type) {}

size_t Bonus::GetX() const {
    return x_;
}

size_t Bonus::GetY() const {
    return y_;
}

BonusType Bonus::GetType() const {
    return type_;
}