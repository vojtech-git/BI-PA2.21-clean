#pragma once
#include "application/ghosts/ghost_collision_presenter.hpp"
#include "presentation/game/board_view.hpp"
#include "presentation/game/hud_view.hpp"

class CursesGhostCollisionPresenter : public GhostCollisionPresenter {
public:
    CursesGhostCollisionPresenter(BoardView &board_view, HudView &hud_view);
    void PresentPlayerDamaged(int player_id, int new_health) override;
    void PresentPlayerDied(int player_id, size_t x, size_t y) override;

private:
    BoardView &board_view_;
    HudView &hud_view_;
};