#pragma once
#include <string>
#include <cstdint>
#include "domain/common/entity_id.hpp"

class Player {
public:
    Player(PlayerId id, std::string name, uint32_t x_position, uint32_t y_position, int health);

    PlayerId GetId() const { return id_; }
    const std::string& GetName() const { return name_; }
    uint32_t GetX() const { return x_position_; }
    uint32_t GetY() const { return y_position_; }
    int GetHealth() const { return health_; }
    uint32_t GetExplosionSize() const { return explosion_size_; }
    float GetBombCooldown() const { return bomb_cooldown_; }

    void Move(uint32_t new_x, uint32_t new_y);
    void TakeDamage(int damage);
    bool IsDead() const;
    void PlantBomb();
    void UpdateCooldown(float dt);
    void UpdateInvulnerability(float dt);
    bool IsInvulnerable() const;

    void AddHealth(int amount);
    void AddExplosionSize();
    void ReduceBombCooldown(float amount);
    void Freeze(float duration);
    void Levitate(float duration);
    bool isFrozen() const;
    bool isLevitating() const;

private:
    PlayerId id_;
    std::string name_;
    uint32_t x_position_;
    uint32_t y_position_;
    int health_;
    float bomb_cooldown_{2.0f};
    uint32_t explosion_size_{1};
    float frozen_timer_{0.0f};
    float levitation_timer_{0.0f};
    float invulnerability_timer_{0.0f};
};