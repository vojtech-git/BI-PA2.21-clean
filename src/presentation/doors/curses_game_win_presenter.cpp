#include "curses_game_win_presenter.hpp"

CursesGameWinPresenter::CursesGameWinPresenter(
    View &root_view,
    AppState &app_state,
    BoardView &board_view,
    HudView &hud_view,
    ControlsView &controls_view
) : root_view_(root_view),
    app_state_(app_state),
    board_view_(board_view),
    hud_view_(hud_view),
    controls_view_(controls_view) {}

void CursesGameWinPresenter::PresentDoorRevealed(size_t x, size_t y) {
    board_view_.AddEntity(x, y, EntityVisualLayer::Door);
}

void CursesGameWinPresenter::PresentGameWon(const std::string &winner_name, int score_seconds) {
    app_state_ = AppState::MainMenu;

    // Clean up game sub-windows
    hud_view_.ClearWindow();
    board_view_.ClearWindow();
    controls_view_.ClearWindow();

    // Render Victory Splash on root screen
    root_view_.ClearScreen();
    // touchwin(root_view_.GetCursesWindow());

    int cx = root_view_.GetWidth() / 2;
    int cy = root_view_.GetHeight() / 2;

    root_view_.DrawText(cx, cy - 2, "=== VICTORY! ===");
    root_view_.DrawText(cx, cy, "Winner: " + winner_name);
    root_view_.DrawText(cx, cy + 1, "Time / Score: " + std::to_string(score_seconds) + "s");
    root_view_.DrawText(cx, cy + 4, "[Press any key to continue to Main Menu]");
    root_view_.Render();
}