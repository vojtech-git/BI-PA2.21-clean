#pragma once

#include "application/players/player_presenter.hpp"
#include "presentation/game/board_view.hpp"
#include "presentation/game/hud_view.hpp"

class CursesPlayerPresenter : public PlayerPresenter {
public:
    CursesPlayerPresenter(BoardView &board_view, HudView &hud_view);

    void PresentPlayerMoved(size_t old_x, size_t old_y, size_t new_x, size_t new_y) override;
    void PresentPlayerDied(size_t x, size_t y) override;
    void PresentBonusCollected(size_t x, size_t y) override;
    void PresentPlayerStatsUpdated(
        uint32_t player_id,
        int health,
        size_t explosion_size,
        float bomb_cooldown,
        bool frozen,
        bool levitating
    ) override;

private:
    BoardView &board_view_;
    HudView &hud_view_;
};