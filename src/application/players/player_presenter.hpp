#pragma once

#include <cstddef>
#include <cstdint>

class PlayerPresenter {
public:
    virtual ~PlayerPresenter() = default;
    virtual void PresentPlayerMoved(size_t old_x, size_t old_y, size_t new_x, size_t new_y) = 0;
    virtual void PresentPlayerDied(size_t x, size_t y) = 0;
    virtual void PresentBonusCollected(size_t x, size_t y) = 0;
    virtual void PresentPlayerStatsUpdated(
        uint32_t player_id,
        int health,
        size_t explosion_size,
        float bomb_cooldown,
        bool frozen,
        bool levitating
    ) = 0;
};