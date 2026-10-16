#include "curses_game_start_presenter.hpp"
#include <algorithm>

CursesGameStartPresenter::CursesGameStartPresenter(
    View &root_view,
    AppState &app_state,
    HudView &hud_view,
    BoardView &board_view,
    ControlsView &controls_view
) : root_view_(root_view),
    app_state_(app_state),
    hud_view_(hud_view),
    board_view_(board_view),
    controls_view_(controls_view) {}

void CursesGameStartPresenter::PresentGameStart(
    const Map &map,
    const std::vector<Wall> &walls,
    const std::vector<Player> &players,
    const std::vector<Ghost> &ghosts,
    const std::optional<Door> &door,
    const GameHudConfig &hud_config
) {
    app_state_ = AppState::Game;

    // Clear and redraw stdscr background
    werase(stdscr);
    wnoutrefresh(stdscr);

    // Read physical terminal dimensions
    int term_h = 0;
    int term_w = 0;
    getmaxyx(stdscr, term_h, term_w);

    // Compute dimensions
    int hud_w = std::min(term_w - 4, 60);
    int hud_h = static_cast<int>(players.size()) + 1;

    int board_w = static_cast<int>(map.GetWidth());
    int board_h = static_cast<int>(map.GetHeight());

    int ctrl_w = std::min(term_w - 2, 50);
    int ctrl_h = static_cast<int>(hud_config.controls.size()) + 2;

    int total_h = hud_h + 1 + board_h + 1 + ctrl_h;
    int start_y = std::max(1, (term_h - total_h) / 2);

    // 1. HUD View
    int hud_y = start_y;
    int hud_x = std::max(0, (term_w - hud_w) / 2);
    hud_view_.InitWindow(hud_y, hud_x, hud_w, hud_h);
    hud_view_.Reset();

    for (size_t i = 0; i < players.size(); ++i) {
        int player_id = static_cast<int>(i);
        const auto &p = players[i];
        hud_view_.AddPlayerSlot(player_id, p.GetName());
        hud_view_.UpdatePlayer(
            player_id,
            p.GetHealth(),
            p.GetExplosionSize(),
            p.GetBombCooldown(),
            p.isFrozen(),
            p.isLevitating()
        );
    }

    // 2. Board View
    int board_y = hud_y + hud_h + 1;
    int board_x = std::max(0, (term_w - board_w) / 2);
    board_view_.InitWindow(board_y, board_x, map.GetWidth(), map.GetHeight());
    board_view_.Clear();

    if (door.has_value() && door->IsRevealed()) {
        board_view_.AddEntity(door->GetX(), door->GetY(), EntityVisualLayer::Door);
    }
    for (const auto &w : walls) {
        auto layer = (w.GetType() == WallType::Hard) ? EntityVisualLayer::HardWall : EntityVisualLayer::SoftWall;
        board_view_.AddEntity(w.GetX(), w.GetY(), layer);
    }
    for (const auto &g : ghosts) {
        board_view_.AddEntity(g.GetX(), g.GetY(), EntityVisualLayer::Ghost);
    }
    for (const auto &p : players) {
        board_view_.AddEntity(p.GetX(), p.GetY(), EntityVisualLayer::Player);
    }

    // 3. Controls View
    int ctrl_y = board_y + board_h + 1;
    int ctrl_x = std::max(0, (term_w - ctrl_w) / 2);
    controls_view_.InitWindow(ctrl_y, ctrl_x, ctrl_w, ctrl_h);
    controls_view_.SetControls(hud_config.controls);
}