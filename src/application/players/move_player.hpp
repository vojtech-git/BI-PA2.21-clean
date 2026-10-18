#pragma once

#include "application/boards/board_repository.hpp"
#include "application/bombs/bomb_repository.hpp"
#include "application/bonuses/bonus_repository.hpp"
#include "application/players/player_presenter.hpp"
#include "application/players/player_repository.hpp"
#include "application/walls/wall_repository.hpp"
#include "domain/common/entity_id.hpp"

class MovePlayer {
public:
    MovePlayer(
        PlayerRepository &player_repo,
        BoardRepository &board_repo,
        WallRepository &wall_repo,
        BombRepository &bomb_repo,
        BonusRepository &bonus_repo,
        PlayerPresenter &presenter
    );

    void Execute(PlayerId player_id, int dx, int dy);

private:
    PlayerRepository &player_repo_;
    BoardRepository &board_repo_;
    WallRepository &wall_repo_;
    BombRepository &bomb_repo_;
    BonusRepository &bonus_repo_;
    PlayerPresenter &presenter_;
};