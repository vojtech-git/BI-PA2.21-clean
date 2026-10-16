#pragma once
#include "application/bombs/bomb_store.hpp"
#include "application/maps/map_store.hpp"
#include "application/walls/wall_store.hpp"
#include "application/players/player_store.hpp"
#include "application/smokes/smoke_store.hpp"
#include "application/bombs/bomb_presenter.hpp"

class TickBombs {
public:
    TickBombs(
        BombStore &bomb_store,
        MapStore &map_store,
        WallStore &wall_store,
        PlayerStore &player_store,
        SmokeStore &smoke_store,
        BombPresenter &presenter
    );
    void Execute(float dt);

private:
    void Explode(size_t bomb_index);
    void CheckDamageTile(size_t x, size_t y);

    BombStore &bomb_store_;
    MapStore &map_store_;
    WallStore &wall_store_;
    PlayerStore &player_store_;
    SmokeStore &smoke_store_;
    BombPresenter &presenter_;
};