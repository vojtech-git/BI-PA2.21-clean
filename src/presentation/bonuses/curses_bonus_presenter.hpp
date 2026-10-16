#pragma once
#include "application/bonuses/bonus_presenter.hpp"
#include "presentation/game/board_view.hpp"
#include "presentation/game/hud_view.hpp"

class CursesBonusPresenter : public BonusPresenter {
public:
    CursesBonusPresenter(BoardView &board_view, HudView &hud_view);
    void PresentBonusSpawned(size_t x, size_t y) override;
    void PresentBonusCollected(size_t x, size_t y) override;
    void PresentPlayerStatsUpdated(
        int player_id,
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