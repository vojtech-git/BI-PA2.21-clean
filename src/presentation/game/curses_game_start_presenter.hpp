#pragma once
#include "application/games/game_start_presenter.hpp"
#include "presentation/view.hpp"
#include "presentation/app_state.hpp"
#include "presentation/game/hud_view.hpp"
#include "presentation/game/board_view.hpp"
#include "presentation/game/controls_view.hpp"

class CursesGameStartPresenter : public GameStartPresenter {
public:
    CursesGameStartPresenter(
        View &root_view,
        AppState &app_state,
        HudView &hud_view,
        BoardView &board_view,
        ControlsView &controls_view
    );

    void PresentGameStart(
        const Board &map,
        const std::vector<Wall> &walls,
        const std::vector<Player> &players,
        const std::vector<Ghost> &ghosts,
        const std::optional<Door> &door,
        const GameHudConfig &hud_config
    ) override;

private:
    View &root_view_;
    AppState &app_state_;
    HudView &hud_view_;
    BoardView &board_view_;
    ControlsView &controls_view_;
};