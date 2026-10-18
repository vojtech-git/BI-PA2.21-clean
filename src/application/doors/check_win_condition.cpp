#include "application/doors/check_win_condition.hpp"

CheckWinCondition::CheckWinCondition(
    PlayerRepository &player_repo,
    DoorRepository &door_repo,
    BoardRepository &board_repo,
    MapSelectionRepository &map_selection_repo,
    LeaderboardRepository &leaderboard_repo,
    GameWinPresenter &presenter
) : player_repo_(player_repo),
    door_repo_(door_repo),
    board_repo_(board_repo),
    map_selection_repo_(map_selection_repo),
    leaderboard_repo_(leaderboard_repo),
    presenter_(presenter) {}

bool CheckWinCondition::Execute() {
    auto board_opt = board_repo_.Get();
    if (!board_opt.has_value() || board_opt->IsGameOver()) {
        return false;
    }

    auto door_opt = door_repo_.Get();
    if (!door_opt.has_value() || !door_opt->IsRevealed()) {
        return false;
    }

    Position door_pos = door_opt->GetPosition();

    for (const auto &player : player_repo_.GetAll()) {
        if (!player.IsDead() && player.GetPosition() == door_pos) {
            Board board = *board_opt;
            board.MarkGameOver();
            board_repo_.Save(board);

            int final_score = static_cast<int>(board.GetElapsedTime());
            std::string map_name = map_selection_repo_.GetSelectedMapName();

            leaderboard_repo_.SaveScore(map_name, {player.GetName(), final_score});
            presenter_.PresentGameWon(player.GetName(), final_score);
            return true;
        }
    }

    return false;
}