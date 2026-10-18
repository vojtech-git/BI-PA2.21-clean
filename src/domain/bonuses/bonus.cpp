#include "domain/bonuses/bonus.hpp"

Bonus::Bonus(BonusId id, uint32_t x_position, uint32_t y_position, BonusType type)
    : id_(id),
      x_position_(x_position),
      y_position_(y_position),
      type_(type) {}

BonusId Bonus::GetId() const {
    return id_;
}

uint32_t Bonus::GetX() const {
    return x_position_;
}

uint32_t Bonus::GetY() const {
    return y_position_;
}

BonusType Bonus::GetType() const {
    return type_;
}