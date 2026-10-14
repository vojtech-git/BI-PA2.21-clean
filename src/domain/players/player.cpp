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