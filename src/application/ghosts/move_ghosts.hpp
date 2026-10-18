#pragma once

#include "application/boards/board_repository.hpp"
#include "application/bombs/bomb_repository.hpp"
#include "application/ghosts/ghost_presenter.hpp"
#include "application/ghosts/ghost_repository.hpp"
#include "application/walls/wall_repository.hpp"

class MoveGhosts {
public:
    MoveGhosts(
        GhostRepository &ghost_repo,
        BoardRepository &board_repo,
        WallRepository &wall_repo,
        BombRepository &bomb_repo,
        GhostPresenter &presenter
    );

    void Execute(float dt);

private:
    GhostRepository &ghost_repo_;
    BoardRepository &board_repo_;
    WallRepository &wall_repo_;
    BombRepository &bomb_repo_;
    GhostPresenter &presenter_;
};