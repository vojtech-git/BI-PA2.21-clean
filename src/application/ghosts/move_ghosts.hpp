#pragma once
#include "application/ghosts/ghost_store.hpp"
#include "application/maps/map_store.hpp"
#include "application/walls/wall_store.hpp"
#include "application/bombs/bomb_store.hpp"
#include "application/ghosts/ghost_presenter.hpp"

class MoveGhosts {
public:
    MoveGhosts(
        GhostStore &ghost_store,
        MapStore &map_store,
        WallStore &wall_store,
        BombStore &bomb_store,
        GhostPresenter &presenter
    );
    void Execute(float dt);

private:
    bool IsTileBlocked(size_t x, size_t y) const;

    GhostStore &ghost_store_;
    MapStore &map_store_;
    WallStore &wall_store_;
    BombStore &bomb_store_;
    GhostPresenter &presenter_;
};