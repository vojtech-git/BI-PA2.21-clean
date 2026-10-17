#pragma once
#include "application/doors/game_win_presenter.hpp"
#include "presentation/view.hpp"
#include "presentation/app_state.hpp"
#include "presentation/game/board_view.hpp"
#include "presentation/game/hud_view.hpp"
#include "presentation/game/controls_view.hpp"

class CursesGameWinPresenter : public GameWinPresenter {
public:
    CursesGameWinPresenter(
        View &root_view,
        AppState &app_state,
        BoardView &board_view,
        HudView &hud_view,
        ControlsView &controls_view
    );

    void PresentDoorRevealed(size_t x, size_t y) override;
    void PresentGameWon(const std::string &winner_name, int score_seconds) override;

private:
    View &root_view_;
    AppState &app_state_;
    BoardView &board_view_;
    HudView &hud_view_;
    ControlsView &controls_view_;
};