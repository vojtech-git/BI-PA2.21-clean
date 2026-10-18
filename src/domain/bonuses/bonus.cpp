#include "domain/bonuses/bonus.hpp"

Bonus::Bonus(BonusId id, Position position, BonusType type)
    : id_(id),
      position_(position),
      type_(type) {}

BonusId Bonus::GetId() const {
    return id_;
}

Position Bonus::GetPosition() const {
    return position_;
}

uint32_t Bonus::GetX() const {
    return position_.x;
}

uint32_t Bonus::GetY() const {
    return position_.y;
}

BonusType Bonus::GetType() const {
    return type_;
}