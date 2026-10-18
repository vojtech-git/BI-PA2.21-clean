#pragma once

#include "application/boards/board_repository.hpp"
#include "application/doors/door_repository.hpp"
#include "application/doors/game_win_presenter.hpp"
#include "application/leaderboards/leaderboard_repository.hpp"
#include "application/maps/map_selection_repository.hpp"
#include "application/players/player_repository.hpp"

class CheckWinCondition {
public:
    CheckWinCondition(
        PlayerRepository &player_repo,
        DoorRepository &door_repo,
        BoardRepository &board_repo,
        MapSelectionRepository &map_selection_repo,
        LeaderboardRepository &leaderboard_repo,
        GameWinPresenter &presenter
    );

    bool Execute();

private:
    PlayerRepository &player_repo_;
    DoorRepository &door_repo_;
    BoardRepository &board_repo_;
    MapSelectionRepository &map_selection_repo_;
    LeaderboardRepository &leaderboard_repo_;
    GameWinPresenter &presenter_;
};