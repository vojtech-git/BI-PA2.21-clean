#include "curses_ghost_presenter.hpp"

CursesGhostPresenter::CursesGhostPresenter(BoardView &board_view)
    : board_view_(board_view) {}

void CursesGhostPresenter::PresentGhostMoved(size_t old_x, size_t old_y, size_t new_x, size_t new_y) {
    board_view_.MoveEntity(old_x, old_y, new_x, new_y, EntityVisualLayer::Ghost);
}