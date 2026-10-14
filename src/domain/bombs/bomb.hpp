#pragma once
#include <cstddef>

class Bomb {
public:
    Bomb(size_t x_position, size_t y_position, size_t explosion_size);
    void UpdateExplosion(float dt);

    size_t GetX() const;
    size_t GetY() const;
    size_t GetExplosionSize() const;
    float GetDetonationTimer() const;

private:
    size_t x_position_;
    size_t y_position_;
    float detonation_timer_;
    size_t explosion_size_;
};