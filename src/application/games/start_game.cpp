#include "application/games/start_game.hpp"
#include "domain/boards/board.hpp"

StartGame::StartGame(
    MapConfigurationRepository &map_config_repo,
    MapSelectionRepository &map_selection_repo,
    BoardRepository &board_repo,
    WallRepository &wall_repo,
    PlayerRepository &player_repo,
    GhostRepository &ghost_repo,
    DoorRepository &door_repo,
    IdGeneratorService &id_generator,
    KeybindService &keybind_service,
    GameStartPresenter &presenter
) : map_config_repo_(map_config_repo),
    map_selection_repo_(map_selection_repo),
    board_repo_(board_repo),
    wall_repo_(wall_repo),
    player_repo_(player_repo),
    ghost_repo_(ghost_repo),
    door_repo_(door_repo),
    id_generator_(id_generator),
    keybind_service_(keybind_service),
    presenter_(presenter) {}

void StartGame::Execute() {
    std::string selected_map = map_selection_repo_.GetSelectedMapName();
    if (selected_map.empty()) return;

    auto map_dto = map_config_repo_.LoadMapConfiguration(selected_map);
    if (!map_dto.has_value()) return;

    PopulateRepositories(*map_dto);
    BindPlayerKeys(*map_dto);

    GameHudConfig config;
    for (const auto &p : map_dto->players) {
        std::string moves = {p.upKey, p.leftKey, p.downKey, p.rightKey};
        config.controls.push_back({p.name, moves, p.bombKey});
    }

    auto active_board = board_repo_.Get();
    if (!active_board.has_value()) return;

    presenter_.PresentGameStart(
        *active_board,
        wall_repo_.GetAll(),
        player_repo_.GetAll(),
        ghost_repo_.GetAll(),
        door_repo_.Get(),
        config
    );
}

void StartGame::PopulateRepositories(const MapDto &dto) {
    board_repo_.Clear();
    wall_repo_.Clear();
    player_repo_.Clear();
    ghost_repo_.Clear();
    door_repo_.Clear();
    id_generator_.ResetAll();

    board_repo_.Save(Board(
        static_cast<uint32_t>(dto.width),
        static_cast<uint32_t>(dto.height),
        dto.bonusChances.flame,
        dto.bonusChances.frozen,
        dto.bonusChances.levitation,
        dto.bonusChances.delay,
        dto.bonusChances.health
    ));

    for (const auto &w : dto.walls) {
        Position pos{static_cast<uint32_t>(w.x), static_cast<uint32_t>(w.y)};
        wall_repo_.Save(Wall(id_generator_.Next<WallId>(), pos, w.type));
    }

    for (const auto &g : dto.ghosts) {
        Position pos{static_cast<uint32_t>(g.x), static_cast<uint32_t>(g.y)};
        ghost_repo_.Save(Ghost(id_generator_.Next<GhostId>(), pos));
    }

    if (dto.hasDoor) {
        Position door_pos{static_cast<uint32_t>(dto.doorPosition.x), static_cast<uint32_t>(dto.doorPosition.y)};
        door_repo_.Save(Door(id_generator_.Next<DoorId>(), door_pos));
    }

    for (const auto &p : dto.players) {
        Position pos{static_cast<uint32_t>(p.x), static_cast<uint32_t>(p.y)};
        player_repo_.Save(Player(id_generator_.Next<PlayerId>(), p.name, pos, 3));
    }
}

void StartGame::BindPlayerKeys(const MapDto &dto) {
    keybind_service_.ClearDynamicKeys();

    auto players = player_repo_.GetAll();
    for (size_t i = 0; i < dto.players.size() && i < players.size(); ++i) {
        const auto &p = dto.players[i];
        PlayerId player_id = players[i].GetId();

        keybind_service_.BindPlayerMove(p.upKey, player_id, MoveDirection::Up);
        keybind_service_.BindPlayerMove(p.leftKey, player_id, MoveDirection::Left);
        keybind_service_.BindPlayerMove(p.downKey, player_id, MoveDirection::Down);
        keybind_service_.BindPlayerMove(p.rightKey, player_id, MoveDirection::Right);
        keybind_service_.BindPlayerBomb(p.bombKey, player_id);
    }
}