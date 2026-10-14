#pragma once
#include <string>
#include <cstddef>

class Player {
public:
    Player(std::string name, size_t x_position, size_t y_position, int health);

    void PlantBomb();
    void AddExplosionSize();
    void Freeze(float freeze_duration);
    void Levitate(float levitation_duration);
    bool isFrozen() const;
    bool isLevitating() const;
    void Move(size_t new_x_position, size_t new_y_position);

    size_t GetX() const;
    size_t GetY() const;
    const std::string& GetName() const;
    int GetHealth() const;
    size_t GetExplosionSize() const;
    float GetBombCooldown() const;

private:
    std::string name_;
    size_t x_position_;
    size_t y_position_;
    int health_;
    float bomb_cooldown_;
    size_t explosion_size_;
    float frozen_timer_;
    float levitation_timer_;
};