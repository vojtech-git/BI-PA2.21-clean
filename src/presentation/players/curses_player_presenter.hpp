#pragma once

#include "application/players/player_presenter.hpp"
#include "presentation/game/game_board_buffer.hpp"

class CursesPlayerPresenter : public PlayerPresenter {
public:
    explicit CursesPlayerPresenter(GameBoardBuffer &buffer);

    void PresentPlayerMoved(size_t old_x, size_t old_y, size_t new_x, size_t new_y) override;
    void PresentPlayerDied(size_t x, size_t y) override;

private:
    GameBoardBuffer &buffer_;
};