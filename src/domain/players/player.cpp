#include "player.hpp"

Player::Player(std::string name, size_t x_position, size_t y_position, int health)
    : name_(std::move(name)),
      x_position_(x_position),
      y_position_(y_position),
      health_(health),
      bomb_cooldown_(2.0f),
      explosion_size_(1),
      frozen_timer_(0.0f),
      levitation_timer_(0.0f) {}

void Player::PlantBomb() {
    bomb_cooldown_ = 2.0f;
}

void Player::AddExplosionSize() {
    explosion_size_ += 1;
}

void Player::Freeze(float freeze_duration) {
    frozen_timer_ = freeze_duration;
}

void Player::Levitate(float levitation_duration) {
    levitation_timer_ = levitation_duration;
}

bool Player::isFrozen() const {
    return frozen_timer_ > 0.0f;
}

bool Player::isLevitating() const {
    return levitation_timer_ > 0.0f;
}

void Player::Move(size_t new_x_position, size_t new_y_position) {
    if (isFrozen()) {
        return;
    }
    x_position_ = new_x_position;
    y_position_ = new_y_position;
}

void Player::UpdateCooldown(float dt) {
    if (bomb_cooldown_ > 0.0f) {
        bomb_cooldown_ = std::max(0.0f, bomb_cooldown_ - dt);
    }
}

size_t Player::GetX() const {
    return x_position_;
}

size_t Player::GetY() const {
    return y_position_;
}

const std::string& Player::GetName() const {
    return name_;
}

int Player::GetHealth() const {
    return health_;
}

size_t Player::GetExplosionSize() const {
    return explosion_size_;
}

float Player::GetBombCooldown() const {
    return bomb_cooldown_;
}

bool Player::IsDead() const {
    return health_ <= 0;
}

void Player::AddHealth(int amount) {
    health_ += amount;
}

void Player::ReduceBombCooldown(float amount) {
    bomb_cooldown_ = std::max(0.5f, bomb_cooldown_ - amount);
}

void Player::TakeDamage(int damage) {
    if (IsInvulnerable() || IsDead()) {
        return;
    }
    health_ -= damage;
    if (health_ < 0) {
        health_ = 0;
    }
    if (!IsDead()) {
        invulnerability_timer_ = 2.0f;
    }
}

bool Player::IsInvulnerable() const {
    return invulnerability_timer_ > 0.0f;
}

void Player::UpdateInvulnerability(float dt) {
    if (invulnerability_timer_ > 0.0f) {
        invulnerability_timer_ = std::max(0.0f, invulnerability_timer_ - dt);
    }
}