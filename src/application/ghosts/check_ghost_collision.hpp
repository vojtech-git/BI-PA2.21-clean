#pragma once

#include "application/ghosts/ghost_collision_presenter.hpp"
#include "application/ghosts/ghost_repository.hpp"
#include "application/players/player_repository.hpp"

class CheckGhostCollision {
public:
    CheckGhostCollision(
        PlayerRepository &player_repo,
        GhostRepository &ghost_repo,
        GhostCollisionPresenter &presenter
    );

    void Execute();

private:
    PlayerRepository &player_repo_;
    GhostRepository &ghost_repo_;
    GhostCollisionPresenter &presenter_;
};