#pragma once
#include <cstddef>

class BombPresenter {
public:
    virtual ~BombPresenter() = default;
    virtual void PresentBombPlaced(size_t x, size_t y) = 0;
    virtual void PresentBombExploded(size_t x, size_t y) = 0;
    virtual void PresentSmokePlaced(size_t x, size_t y) = 0;
    virtual void PresentWallDestroyed(size_t x, size_t y) = 0;
    virtual void PresentSmokeRemoved(size_t x, size_t y) = 0;
    virtual void PresentPlayerDamaged(int player_id, int new_health) = 0;
    virtual void PresentPlayerDied(int player_id, size_t x, size_t y) = 0;
    virtual void PresentGhostDied(size_t x, size_t y) = 0;
};