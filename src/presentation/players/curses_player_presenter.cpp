#include "presentation/players/curses_player_presenter.hpp"

CursesPlayerPresenter::CursesPlayerPresenter(BoardView &board_view, HudView &hud_view)
    : board_view_(board_view), hud_view_(hud_view) {}

void CursesPlayerPresenter::PresentPlayerMoved(size_t old_x, size_t old_y, size_t new_x, size_t new_y) {
    board_view_.MoveEntity(old_x, old_y, new_x, new_y, EntityVisualLayer::Player);
}

void CursesPlayerPresenter::PresentPlayerDied(size_t x, size_t y) {
    board_view_.RemoveEntity(x, y, EntityVisualLayer::Player);
}

void CursesPlayerPresenter::PresentBonusCollected(size_t x, size_t y) {
    board_view_.RemoveEntity(x, y, EntityVisualLayer::Bonus);
}

void CursesPlayerPresenter::PresentPlayerStatsUpdated(
    uint32_t player_id,
    int health,
    size_t explosion_size,
    float bomb_cooldown,
    bool frozen,
    bool levitating
) {
    hud_view_.UpdatePlayer(
        static_cast<int>(player_id),
        health,
        explosion_size,
        bomb_cooldown,
        frozen,
        levitating
    );
}