#include "smoke.hpp"

Smoke::Smoke(size_t x_position, size_t y_position, size_t size)
{
    x_position_ = x_position;
    y_position_ = y_position;
    size_ = size;
    smoke_timer_ = 4.0f;
}