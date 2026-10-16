#pragma once
#include "application/players/player_store.hpp"
#include "application/ghosts/ghost_store.hpp"
#include "application/ghosts/ghost_collision_presenter.hpp"

class CheckGhostCollision {
public:
    CheckGhostCollision(
        PlayerStore &player_store,
        GhostStore &ghost_store,
        GhostCollisionPresenter &presenter
    );
    void Execute();

private:
    PlayerStore &player_store_;
    GhostStore &ghost_store_;
    GhostCollisionPresenter &presenter_;
};