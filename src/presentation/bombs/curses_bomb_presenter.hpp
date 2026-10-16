#pragma once
#include "application/bombs/bomb_presenter.hpp"
#include "presentation/game/board_view.hpp"
#include "presentation/game/hud_view.hpp"

class CursesBombPresenter : public BombPresenter {
public:
    explicit CursesBombPresenter(BoardView &board_view, HudView &hud_view);
    void PresentBombPlaced(size_t x, size_t y) override;
    void PresentBombExploded(size_t x, size_t y) override;
    void PresentSmokePlaced(size_t x, size_t y) override;
    void PresentWallDestroyed(size_t x, size_t y) override;
    void PresentSmokeRemoved(size_t x, size_t y) override;
    void PresentPlayerDamaged(int player_id, int new_health) override;
    void PresentPlayerDied(int player_id, size_t x, size_t y) override;
    void PresentGhostDied(size_t x, size_t y) override;

private:
    BoardView &board_view_;
    HudView &hud_view_;
};