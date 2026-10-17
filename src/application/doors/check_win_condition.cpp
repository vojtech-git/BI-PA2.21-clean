#include "check_win_condition.hpp"

CheckWinCondition::CheckWinCondition(
    PlayerStore &player_store,
    DoorStore &door_store,
    MapStore &map_store,
    LeaderboardRepository &leaderboard_repo,
    GameWinPresenter &presenter
) : player_store_(player_store),
    door_store_(door_store),
    map_store_(map_store),
    leaderboard_repo_(leaderboard_repo),
    presenter_(presenter) {}

void CheckWinCondition::ResetTimer() {
    game_timer_ = 0.0f;
    won_ = false;
}

void CheckWinCondition::UpdateTime(float dt) {
    if (!won_) {
        game_timer_ += dt;
    }
}

bool CheckWinCondition::Execute() {
    if (won_) return true;

    auto door = door_store_.Get();
    if (!door.has_value() || !door->IsRevealed()) {
        return false;
    }

    for (const auto &player : player_store_.GetAll()) {
        if (!player.IsDead() && player.GetX() == door->GetX() && player.GetY() == door->GetY()) {
            won_ = true;
            int final_score = static_cast<int>(game_timer_);

            std::string map_name = map_store_.GetSelectedMapName();
            leaderboard_repo_.SaveScore(map_name, {player.GetName(), final_score});

            presenter_.PresentGameWon(player.GetName(), final_score);
            return true;
        }
    }
    return false;
}