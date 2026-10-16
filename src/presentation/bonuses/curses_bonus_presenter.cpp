#include "curses_bonus_presenter.hpp"

CursesBonusPresenter::CursesBonusPresenter(BoardView &board_view, HudView &hud_view)
    : board_view_(board_view), hud_view_(hud_view) {}

void CursesBonusPresenter::PresentBonusSpawned(size_t x, size_t y) {
    board_view_.AddEntity(x, y, EntityVisualLayer::Bonus);
}

void CursesBonusPresenter::PresentBonusCollected(size_t x, size_t y) {
    board_view_.RemoveEntity(x, y, EntityVisualLayer::Bonus);
}

void CursesBonusPresenter::PresentPlayerStatsUpdated(
    int player_id,
    int health,
    size_t explosion_size,
    float bomb_cooldown,
    bool frozen,
    bool levitating
) {
    hud_view_.UpdatePlayer(player_id, health, explosion_size, bomb_cooldown, frozen, levitating);
}