#pragma once
#include <cstddef>

class Door {
public:
    Door(size_t x_position, size_t y_position);

    void Reveal();
    bool IsRevealed() const;
    size_t GetX() const;
    size_t GetY() const;

private:
    size_t x_position_;
    size_t y_position_;
    bool revealed_;
};