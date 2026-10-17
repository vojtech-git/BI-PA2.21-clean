#pragma once
#include "application/players/player_store.hpp"
#include "application/doors/door_store.hpp"
#include "application/maps/map_store.hpp"
#include "application/leaderboards/leaderboard_repository.hpp"
#include "application/doors/game_win_presenter.hpp"

class CheckWinCondition {
public:
    CheckWinCondition(
        PlayerStore &player_store,
        DoorStore &door_store,
        MapStore &map_store,
        LeaderboardRepository &leaderboard_repo,
        GameWinPresenter &presenter
    );

    void ResetTimer();
    void UpdateTime(float dt);
    bool Execute();

private:
    PlayerStore &player_store_;
    DoorStore &door_store_;
    MapStore &map_store_;
    LeaderboardRepository &leaderboard_repo_;
    GameWinPresenter &presenter_;
    float game_timer_{0.0f};
    bool won_{false};
};