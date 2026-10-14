#pragma once

class Smoke
{
public:
    Smoke(size_t x_position, size_t y_position, size_t size);
private:
    size_t x_position_;
    size_t y_position_;
    float smoke_timer_;
    size_t size_;
};
