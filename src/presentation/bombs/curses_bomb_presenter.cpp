#include "presentation/bombs/curses_bomb_presenter.hpp"

CursesBombPresenter::CursesBombPresenter(BoardView &board_view, HudView &hud_view)
    : board_view_(board_view), hud_view_(hud_view) {}

void CursesBombPresenter::PresentBombPlaced(size_t x, size_t y) {
    board_view_.AddEntity(x, y, EntityVisualLayer::Bomb);
}

void CursesBombPresenter::PresentBombExploded(size_t x, size_t y) {
    board_view_.RemoveEntity(x, y, EntityVisualLayer::Bomb);
}

void CursesBombPresenter::PresentSmokePlaced(size_t x, size_t y) {
    board_view_.AddEntity(x, y, EntityVisualLayer::Smoke);
}

void CursesBombPresenter::PresentSmokeRemoved(size_t x, size_t y) {
    board_view_.RemoveEntity(x, y, EntityVisualLayer::Smoke);
}

void CursesBombPresenter::PresentWallDestroyed(size_t x, size_t y) {
    board_view_.RemoveEntity(x, y, EntityVisualLayer::SoftWall);
}

void CursesBombPresenter::PresentPlayerDamaged(int player_id, int new_health) {
    hud_view_.UpdatePlayerHealth(player_id, new_health);
}

void CursesBombPresenter::PresentPlayerDied(int player_id, size_t x, size_t y) {
    board_view_.RemoveEntity(x, y, EntityVisualLayer::Player);
    hud_view_.UpdatePlayerHealth(player_id, 0);
}

void CursesBombPresenter::PresentGhostDied(size_t x, size_t y) {
    board_view_.RemoveEntity(x, y, EntityVisualLayer::Ghost);
}

void CursesBombPresenter::PresentBonusSpawned(size_t x, size_t y) {
    board_view_.AddEntity(x, y, EntityVisualLayer::Bonus);
}