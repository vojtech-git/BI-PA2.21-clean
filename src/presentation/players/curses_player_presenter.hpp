#pragma once

#include "application/players/player_presenter.hpp"
#include "presentation/game/board_view.hpp"

class CursesPlayerPresenter : public PlayerPresenter {
public:
    explicit CursesPlayerPresenter(BoardView &board_view);

    void PresentPlayerMoved(size_t old_x, size_t old_y, size_t new_x, size_t new_y) override;
    void PresentPlayerDied(size_t x, size_t y) override;

private:
    BoardView &board_view_;
};