#include "curses_player_presenter.hpp"

CursesPlayerPresenter::CursesPlayerPresenter(GameBoardBuffer &buffer)
    : buffer_(buffer) {}

void CursesPlayerPresenter::PresentPlayerMoved(size_t old_x, size_t old_y, size_t new_x, size_t new_y) {
    buffer_.MoveEntity(old_x, old_y, new_x, new_y, EntityVisualLayer::Player);
}

void CursesPlayerPresenter::PresentPlayerDied(size_t x, size_t y) {
    buffer_.RemoveEntity(x, y, EntityVisualLayer::Player);
}