#pragma once

#include "application/boards/board_repository.hpp"
#include "application/common/id_generator_service.hpp"
#include "application/doors/check_win_condition.hpp"
#include "application/doors/door_repository.hpp"
#include "application/games/game_start_presenter.hpp"
#include "application/ghosts/ghost_repository.hpp"
#include "application/input/keybind_service.hpp"
#include "application/maps/map_configuration_repository.hpp"
#include "application/maps/map_selection_repository.hpp"
#include "application/players/move_player.hpp"
#include "application/players/place_bomb.hpp"
#include "application/players/player_repository.hpp"
#include "application/walls/wall_repository.hpp"

class StartGame {
public:
    StartGame(
        MapConfigurationRepository &map_config_repo,
        MapSelectionRepository &map_selection_repo,
        BoardRepository &board_repo,
        WallRepository &wall_repo,
        PlayerRepository &player_repo,
        GhostRepository &ghost_repo,
        DoorRepository &door_repo,
        IdGeneratorService &id_generator,
        KeybindService &keybind_service,
        MovePlayer &move_player,
        PlaceBomb &place_bomb,
        GameStartPresenter &presenter,
        CheckWinCondition &check_win_condition
    );

    void Execute();

private:
    void PopulateRepositories(const MapDto &dto);
    void BindPlayerKeys(const MapDto &dto);

    MapConfigurationRepository &map_config_repo_;
    MapSelectionRepository &map_selection_repo_;
    BoardRepository &board_repo_;
    WallRepository &wall_repo_;
    PlayerRepository &player_repo_;
    GhostRepository &ghost_repo_;
    DoorRepository &door_repo_;
    IdGeneratorService &id_generator_;
    KeybindService &keybind_service_;
    MovePlayer &move_player_;
    PlaceBomb &place_bomb_;
    GameStartPresenter &presenter_;
    CheckWinCondition &check_win_condition_;
};