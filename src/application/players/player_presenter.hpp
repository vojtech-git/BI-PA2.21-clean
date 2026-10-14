#pragma once
#include <cstddef>

class PlayerPresenter {
public:
    virtual ~PlayerPresenter() = default;
    virtual void PresentPlayerMoved(size_t old_x, size_t old_y, size_t new_x, size_t new_y) = 0;
    virtual void PresentPlayerDied(size_t x, size_t y) = 0;
};