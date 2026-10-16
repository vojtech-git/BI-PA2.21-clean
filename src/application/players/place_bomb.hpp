#pragma once
#include "application/players/player_store.hpp"
#include "application/bombs/bomb_store.hpp"
#include "application/bombs/bomb_presenter.hpp"

class PlaceBomb {
public:
    PlaceBomb(
        PlayerStore &player_store,
        BombStore &bomb_store,
        BombPresenter &presenter
    );
    void Execute(int player_id);

private:
    PlayerStore &player_store_;
    BombStore &bomb_store_;
    BombPresenter &presenter_;
};