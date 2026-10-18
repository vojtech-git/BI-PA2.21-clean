#include "domain/players/player.hpp"
#include "domain/common/game_constants.hpp"
#include <algorithm>
#include <utility>

Player::Player(PlayerId id, std::string name, Position position, int health)
    : id_(id),
      name_(std::move(name)),
      position_(position),
      health_(std::max(0, health)),
      max_bomb_cooldown_(domain::config::player::kInitialBombCooldown),
      explosion_size_(domain::config::player::kInitialExplosionSize) {}

PlayerId Player::GetId() const {
    return id_;
}

const std::string& Player::GetName() const {
    return name_;
}

Position Player::GetPosition() const {
    return position_;
}

uint32_t Player::GetX() const {
    return position_.x;
}

uint32_t Player::GetY() const {
    return position_.y;
}

int Player::GetHealth() const {
    return health_;
}

uint32_t Player::GetExplosionSize() const {
    return explosion_size_;
}

float Player::GetBombCooldown() const {
    return bomb_cooldown_timer_;
}

float Player::GetMaxBombCooldown() const {
    return max_bomb_cooldown_;
}

void Player::Move(Position new_position) {
    if (IsDead() || IsFrozen()) {
        return;
    }
    position_ = new_position;
}

void Player::Move(uint32_t new_x, uint32_t new_y) {
    Move(Position{new_x, new_y});
}

void Player::TakeDamage(int damage) {
    if (damage <= 0 || IsInvulnerable() || IsDead()) {
        return;
    }

    health_ = std::max(0, health_ - damage);

    if (!IsDead()) {
        invulnerability_timer_ = domain::config::player::kInvulnerabilityDuration;
    }
}

bool Player::IsDead() const {
    return health_ <= 0;
}

bool Player::CanPlantBomb() const {
    return !IsDead() && !IsFrozen() && bomb_cooldown_timer_ <= 0.0f;
}

void Player::PlantBomb() {
    bomb_cooldown_timer_ = max_bomb_cooldown_;
}

void Player::UpdateCooldown(float dt) {
    if (bomb_cooldown_timer_ > 0.0f) {
        bomb_cooldown_timer_ = std::max(0.0f, bomb_cooldown_timer_ - dt);
    }
}

void Player::UpdateInvulnerability(float dt) {
    if (invulnerability_timer_ > 0.0f) {
        invulnerability_timer_ = std::max(0.0f, invulnerability_timer_ - dt);
    }
}

void Player::UpdateFreeze(float dt) {
    if (frozen_timer_ > 0.0f) {
        frozen_timer_ = std::max(0.0f, frozen_timer_ - dt);
    }
}

void Player::UpdateLevitation(float dt) {
    if (levitation_timer_ > 0.0f) {
        levitation_timer_ = std::max(0.0f, levitation_timer_ - dt);
    }
}

bool Player::IsInvulnerable() const {
    return invulnerability_timer_ > 0.0f;
}

bool Player::IsFrozen() const {
    return frozen_timer_ > 0.0f;
}

bool Player::IsLevitating() const {
    return levitation_timer_ > 0.0f;
}

void Player::ApplyBonus(BonusType type) {
    switch (type) {
        case BonusType::FlameLength:
            explosion_size_ += domain::config::bonus::kExplosionBonus;
            break;
        case BonusType::BombCooldown:
            max_bomb_cooldown_ = std::max(
                domain::config::player::kMinBombCooldown,
                max_bomb_cooldown_ - domain::config::bonus::kCooldownReduction
            );
            break;
        case BonusType::Health:
            health_ += domain::config::bonus::kHealthBonus;
            break;
        case BonusType::Freeze:
            frozen_timer_ = domain::config::bonus::kFreezeDuration;
            break;
        case BonusType::Levitation:
            levitation_timer_ = domain::config::bonus::kLevitationDuration;
            break;
    }
}