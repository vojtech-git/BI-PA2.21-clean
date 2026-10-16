#pragma once
#include <cstddef>

class Ghost {
public:
    Ghost(size_t x_position, size_t y_position);

    void Update(float dt);
    bool CanMove() const;
    void ResetTimer();

    void Move(size_t new_x_position, size_t new_y_position);
    size_t GetX() const { return x_position_; }
    size_t GetY() const { return y_position_; }

private:
    size_t x_position_;
    size_t y_position_;
    float movement_timer_;
    float move_interval_{1.0f};
};