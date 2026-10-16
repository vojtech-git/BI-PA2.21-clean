#pragma once
#include "player_store.hpp"
#include "player_presenter.hpp"
#include "application/maps/map_store.hpp"
#include "application/walls/wall_store.hpp"
#include "application/bombs/bomb_store.hpp"
#include "application/bonuses/collect_bonuses.hpp"

class MovePlayer {
public:
    MovePlayer(
        PlayerStore &player_store,
        MapStore &map_store,
        WallStore &wall_store,
        BombStore &bomb_store,
        CollectBonuses &collect_bonuses,
        PlayerPresenter &presenter
    );
    void Execute(int player_id, int dx, int dy);

private:
    bool IsTileBlocked(size_t x, size_t y, bool is_levitating) const;
    PlayerStore &player_store_;
    MapStore &map_store_;
    WallStore &wall_store_;
    BombStore &bomb_store_;
    CollectBonuses &collect_bonuses_;
    PlayerPresenter &presenter_;
};