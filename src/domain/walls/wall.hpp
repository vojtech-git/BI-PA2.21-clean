#pragma once
#include <cstddef>

enum class WallType {
    Soft,
    Hard
};

class Wall {
public:
    Wall(size_t x_position, size_t y_position, WallType type);

    size_t GetX() const;
    size_t GetY() const;
    WallType GetType() const;

private:
    size_t x_position_;
    size_t y_position_;
    WallType type_;
};