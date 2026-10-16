#include "curses_ghost_collision_presenter.hpp"

CursesGhostCollisionPresenter::CursesGhostCollisionPresenter(BoardView &board_view, HudView &hud_view)
    : board_view_(board_view), hud_view_(hud_view) {}

void CursesGhostCollisionPresenter::PresentPlayerDamaged(int player_id, int new_health) {
    hud_view_.UpdatePlayerHealth(player_id, new_health);
}

void CursesGhostCollisionPresenter::PresentPlayerDied(int player_id, size_t x, size_t y) {
    board_view_.RemoveEntity(x, y, EntityVisualLayer::Player);
    hud_view_.UpdatePlayerHealth(player_id, 0);
}