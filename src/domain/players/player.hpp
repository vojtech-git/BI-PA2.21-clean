#pragma once
#include <string>
#include <cstdint>
#include "domain/common/entity_id.hpp"
#include "domain/common/position.hpp"
#include "domain/bonuses/bonus.hpp"

class Player {
public:
    Player(PlayerId id, std::string name, Position position, int health);

    PlayerId GetId() const;
    const std::string& GetName() const;
    Position GetPosition() const;
    uint32_t GetX() const;
    uint32_t GetY() const;
    int GetHealth() const;
    uint32_t GetExplosionSize() const;
    float GetBombCooldown() const;
    float GetMaxBombCooldown() const;

    void Move(Position new_position);
    void Move(uint32_t new_x, uint32_t new_y);
    void TakeDamage(int damage);
    bool IsDead() const;

    bool CanPlantBomb() const;
    void PlantBomb();

    void UpdateCooldown(float dt);
    void UpdateInvulnerability(float dt);
    void UpdateFreeze(float dt);
    void UpdateLevitation(float dt);

    bool IsInvulnerable() const;
    bool IsFrozen() const;
    bool IsLevitating() const;

    void ApplyBonus(BonusType type);

private:
    PlayerId id_;
    std::string name_;
    Position position_;
    int health_;
    float bomb_cooldown_timer_{0.0f};
    float max_bomb_cooldown_{0.0f};
    uint32_t explosion_size_{0};
    float frozen_timer_{0.0f};
    float levitation_timer_{0.0f};
    float invulnerability_timer_{0.0f};
};