#pragma once
#include "domain/bonuses/bonus.hpp"
#include <cstddef>

class BonusPresenter {
public:
    virtual ~BonusPresenter() = default;
    virtual void PresentBonusSpawned(size_t x, size_t y) = 0;
    virtual void PresentBonusCollected(size_t x, size_t y) = 0;
    virtual void PresentPlayerStatsUpdated(
        int player_id,
        int health,
        size_t explosion_size,
        float bomb_cooldown,
        bool frozen,
        bool levitating
    ) = 0;
};