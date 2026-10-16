#pragma once
#include <cstddef>
#include <vector>
#include "application/bombs/bomb_store.hpp"
#include "application/maps/map_store.hpp"
#include "application/walls/wall_store.hpp"
#include "application/players/player_store.hpp"
#include "application/ghosts/ghost_store.hpp"
#include "application/smokes/smoke_store.hpp"
#include "application/bombs/bomb_presenter.hpp"
#include "application/bonuses/bonus_store.hpp"
#include "application/bonuses/bonus_presenter.hpp"

class TickBombs {
public:
    TickBombs(
        BombStore &bomb_store,
        MapStore &map_store,
        WallStore &wall_store,
        PlayerStore &player_store,
        GhostStore &ghost_store,
        SmokeStore &smoke_store,
        BonusStore &bonus_store,
        BombPresenter &presenter,
        BonusPresenter &bonus_presenter
    );
    void Execute(float dt);

private:
    void Explode(size_t bomb_index);
    void CheckDamageTile(size_t x, size_t y);
    void TrySpawnBonus(size_t x, size_t y);

    BombStore &bomb_store_;
    MapStore &map_store_;
    WallStore &wall_store_;
    PlayerStore &player_store_;
    GhostStore &ghost_store_;
    SmokeStore &smoke_store_;
    BonusStore &bonus_store_;
    BombPresenter &presenter_;
    BonusPresenter &bonus_presenter_;
};