#pragma once

#include "application/boards/board_repository.hpp"
#include "application/bombs/bomb_presenter.hpp"
#include "application/bombs/bomb_repository.hpp"
#include "application/bonuses/bonus_repository.hpp"
#include "application/common/id_generator_service.hpp"
#include "application/doors/door_repository.hpp"
#include "application/doors/game_win_presenter.hpp"
#include "application/ghosts/ghost_repository.hpp"
#include "application/players/player_repository.hpp"
#include "application/smokes/smoke_repository.hpp"
#include "application/walls/wall_repository.hpp"
#include "domain/bombs/bomb.hpp"

class TickBombs {
public:
    TickBombs(
        BombRepository &bomb_repo,
        BoardRepository &board_repo,
        WallRepository &wall_repo,
        PlayerRepository &player_repo,
        GhostRepository &ghost_repo,
        DoorRepository &door_repo,
        SmokeRepository &smoke_repo,
        BonusRepository &bonus_repo,
        IdGeneratorService &id_generator,
        BombPresenter &presenter,
        GameWinPresenter &win_presenter
    );

    void Execute(float dt);

private:
    void Explode(const Bomb &bomb, const Board &board);
    void TrySpawnBonus(Position pos, const Board &board);
    void CheckDoorReveal(Position pos);

    BombRepository &bomb_repo_;
    BoardRepository &board_repo_;
    WallRepository &wall_repo_;
    PlayerRepository &player_repo_;
    GhostRepository &ghost_repo_;
    DoorRepository &door_repo_;
    SmokeRepository &smoke_repo_;
    BonusRepository &bonus_repo_;
    IdGeneratorService &id_generator_;
    BombPresenter &presenter_;
    GameWinPresenter &win_presenter_;
};