#pragma once

#include <cstddef>
#include "domain/common/entity_id.hpp"

class GhostCollisionPresenter {
public:
    virtual ~GhostCollisionPresenter() = default;
    virtual void PresentPlayerDamaged(PlayerId player_id, int new_health) = 0;
    virtual void PresentPlayerDied(PlayerId player_id, size_t x, size_t y) = 0;
};