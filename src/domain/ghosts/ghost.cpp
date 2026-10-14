#include "ghost.hpp"

Ghost::Ghost(size_t x_position, size_t y_position)
{
    x_position_ = x_position;
    y_position_ = y_position;
    movement_timer_ = 3.0f;
}

void Ghost::Move(size_t new_x_position, size_t new_y_position)
{
    // count new position and check against map boundaries walls and bombs (i guess i should do this in the application layer and here we only apply the data)

    x_position_ = new_x_position;
    y_position_ = new_y_position;
    movement_timer_ = 3.0f;
}
