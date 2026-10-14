#pragma once

#include "application/games/game_presenter.hpp"
#include "application/games/game_hud_state.hpp"
#include "application/players/player_store.hpp"
#include "presentation/view.hpp"
#include "presentation/app_state.hpp"
#include "presentation/game/game_board_buffer.hpp"

class CursesGamePresenter : public GamePresenter {
public:
    CursesGamePresenter(View &view, AppState &app_state, GameBoardBuffer &buffer, const PlayerStore &player_store);

    void SetHudConfig(const GameHudConfig &config) override;

    void PresentGame(
        const Map &map,
        const std::vector<Wall> &walls,
        const std::vector<Player> &players,
        const std::vector<Ghost> &ghosts,
        const std::optional<Door> &door
    ) override;

    void Render();

private:
    void RenderHudTop(int startY);
    void RenderControlsBottom(int startY);

    View &view_;
    AppState &app_state_;
    GameBoardBuffer &buffer_;
    const PlayerStore &player_store_;
    GameHudConfig hud_config_;
};