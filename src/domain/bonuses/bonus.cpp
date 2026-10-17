#include "domain/bonuses/bonus.hpp"
#include "domain/players/player.hpp"

Bonus::Bonus(BonusId id, uint32_t x, uint32_t y, BonusType type)
    : id_(id), x_(x), y_(y), type_(type) {}

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