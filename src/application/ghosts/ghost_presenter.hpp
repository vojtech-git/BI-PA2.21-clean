#pragma once
#include <cstddef>

class GhostPresenter {
public:
    virtual ~GhostPresenter() = default;
    virtual void PresentGhostMoved(size_t old_x, size_t old_y, size_t new_x, size_t new_y) = 0;
};