#pragma once
#include <string>
#include <cstdint>
#include "domain/common/entity_id.hpp"
#include "domain/bonuses/bonus.hpp" // or include the standalone BonusType header

class Player {
public:
    Player(PlayerId id, std::string name, uint32_t x_position, uint32_t y_position, int health);

    PlayerId GetId() const;
    const std::string& GetName() const;
    uint32_t GetX() const;
    uint32_t GetY() const;
    int GetHealth() const;
    uint32_t GetExplosionSize() const;
    float GetBombCooldown() const;

    void Move(uint32_t new_x, uint32_t new_y);
    void TakeDamage(int damage);
    bool IsDead() const;
    void PlantBomb();
    void UpdateCooldown(float dt);
    void UpdateInvulnerability(float dt);
    bool IsInvulnerable() const;

    void ApplyBonus(BonusType type);

    bool IsFrozen() const;
    bool IsLevitating() const;

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