#pragma once
#include "application/ghosts/ghost_presenter.hpp"
#include "presentation/game/board_view.hpp"

class CursesGhostPresenter : public GhostPresenter {
public:
    explicit CursesGhostPresenter(BoardView &board_view);
    void PresentGhostMoved(size_t old_x, size_t old_y, size_t new_x, size_t new_y) override;

private:
    BoardView &board_view_;
};