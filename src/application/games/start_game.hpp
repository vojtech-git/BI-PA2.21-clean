#pragma once

#include "application/maps/map_repository.hpp"
#include "application/maps/map_store.hpp"
#include "application/walls/wall_store.hpp"
#include "application/players/player_store.hpp"
#include "application/ghosts/ghost_store.hpp"
#include "application/doors/door_store.hpp"
#include "application/input/keybind_service.hpp"
#include "application/players/move_player.hpp"
#include "game_presenter.hpp"

class StartGame {
public:
    StartGame(
        MapRepository &map_repo,
        MapStore &map_store,
        WallStore &wall_store,
        PlayerStore &player_store,
        GhostStore &ghost_store,
        DoorStore &door_store,
        KeybindService &keybind_service,
        MovePlayer &move_player,
        GamePresenter &presenter
    );

    void Execute();

private:
    void PopulateStores(const MapDto &dto);
    void BindPlayerKeys(const MapDto &dto);

    MapRepository &map_repo_;
    MapStore &map_store_;
    WallStore &wall_store_;
    PlayerStore &player_store_;
    GhostStore &ghost_store_;
    DoorStore &door_store_;
    KeybindService &keybind_service_;
    MovePlayer &move_player_;
    GamePresenter &presenter_;
};