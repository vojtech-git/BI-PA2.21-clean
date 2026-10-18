#include "domain/bonuses/bonus.hpp"
#include "domain/players/player.hpp"

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

void Bonus::ApplyTo(Player &player) const {
    switch (type_) {
        case BonusType::FlameLength:
            player.AddExplosionSize();
            break;
        case BonusType::BombCooldown:
            player.ReduceBombCooldown(0.3f);
            break;
        case BonusType::Health:
            player.AddHealth(1);
            break;
        case BonusType::Freeze:
            player.Freeze(3.0f);
            break;
        case BonusType::Levitation:
            player.Levitate(5.0f);
            break;
    }
}