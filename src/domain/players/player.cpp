#include "domain/players/player.hpp"
#include <algorithm>
#include <utility>

Player::Player(PlayerId id, std::string name, uint32_t x_position, uint32_t y_position, int health)
    : id_(id),
      name_(std::move(name)),
      x_position_(x_position),
      y_position_(y_position),
      health_(health) {}

PlayerId Player::GetId() const {
    return id_;
}

const std::string& Player::GetName() const {
    return name_;
}

uint32_t Player::GetX() const {
    return x_position_;
}

uint32_t Player::GetY() const {
    return y_position_;
}

int Player::GetHealth() const {
    return health_;
}

uint32_t Player::GetExplosionSize() const {
    return explosion_size_;
}

float Player::GetBombCooldown() const {
    return bomb_cooldown_;
}

void Player::Move(uint32_t new_x, uint32_t new_y) {
    if (IsFrozen()) {
        return;
    }
    x_position_ = new_x;
    y_position_ = new_y;
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

bool Player::IsDead() const {
    return health_ <= 0;
}

void Player::PlantBomb() {
    bomb_cooldown_ = 2.0f;
}

void Player::UpdateCooldown(float dt) {
    if (bomb_cooldown_ > 0.0f) {
        bomb_cooldown_ = std::max(0.0f, bomb_cooldown_ - dt);
    }
}

void Player::UpdateInvulnerability(float dt) {
    if (invulnerability_timer_ > 0.0f) {
        invulnerability_timer_ = std::max(0.0f, invulnerability_timer_ - dt);
    }
}

bool Player::IsInvulnerable() const {
    return invulnerability_timer_ > 0.0f;
}

void Player::AddHealth(int amount) {
    health_ += amount;
}

void Player::AddExplosionSize() {
    explosion_size_ += 1;
}

void Player::ReduceBombCooldown(float amount) {
    bomb_cooldown_ = std::max(0.5f, bomb_cooldown_ - amount);
}

void Player::Freeze(float duration) {
    frozen_timer_ = duration;
}

void Player::Levitate(float duration) {
    levitation_timer_ = duration;
}

bool Player::IsFrozen() const {
    return frozen_timer_ > 0.0f;
}

bool Player::IsLevitating() const {
    return levitation_timer_ > 0.0f;
}