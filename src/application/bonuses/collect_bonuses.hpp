#pragma once
#include "application/players/player_store.hpp"
#include "application/bonuses/bonus_store.hpp"
#include "application/bonuses/bonus_presenter.hpp"

class CollectBonuses {
public:
    CollectBonuses(
        PlayerStore &player_store,
        BonusStore &bonus_store,
        BonusPresenter &presenter
    );
    void Execute(int player_id);

private:
    void ApplyBonus(Player &player, BonusType type);

    PlayerStore &player_store_;
    BonusStore &bonus_store_;
    BonusPresenter &presenter_;
};