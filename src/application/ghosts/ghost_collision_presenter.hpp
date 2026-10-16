#pragma once
#include <cstddef>

class GhostCollisionPresenter {
public:
    virtual ~GhostCollisionPresenter() = default;
    virtual void PresentPlayerDamaged(int player_id, int new_health) = 0;
    virtual void PresentPlayerDied(int player_id, size_t x, size_t y) = 0;
};