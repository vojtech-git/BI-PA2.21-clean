#pragma once
#include <cstddef>

class Smoke {
public:
    Smoke(size_t x_position, size_t y_position, size_t size);

    void Update(float dt);
    bool IsExpired() const;

    size_t GetX() const;
    size_t GetY() const;

private:
    size_t x_position_;
    size_t y_position_;
    float smoke_timer_;
    size_t size_;
};