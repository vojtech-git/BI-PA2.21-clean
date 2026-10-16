#include "curses_player_presenter.hpp"

CursesPlayerPresenter::CursesPlayerPresenter(BoardView &board_view)
    : board_view_(board_view) {}

void CursesPlayerPresenter::PresentPlayerMoved(size_t old_x, size_t old_y, size_t new_x, size_t new_y) {
    board_view_.MoveEntity(old_x, old_y, new_x, new_y, EntityVisualLayer::Player);
}

void CursesPlayerPresenter::PresentPlayerDied(size_t x, size_t y) {
    board_view_.RemoveEntity(x, y, EntityVisualLayer::Player);
}