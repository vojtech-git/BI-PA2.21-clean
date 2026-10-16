#include "start_game.hpp"

StartGame::StartGame(
    MapRepository &map_repo,
    MapStore &map_store,
    WallStore &wall_store,
    PlayerStore &player_store,
    GhostStore &ghost_store,
    DoorStore &door_store,
    KeybindService &keybind_service,
    MovePlayer &move_player,
    PlaceBomb &place_bomb,
    GameStartPresenter &presenter
) : map_repo_(map_repo),
    map_store_(map_store),
    wall_store_(wall_store),
    player_store_(player_store),
    ghost_store_(ghost_store),
    door_store_(door_store),
    keybind_service_(keybind_service),
    move_player_(move_player),
    place_bomb_(place_bomb),
    presenter_(presenter) {}

void StartGame::Execute() {
    std::string selectedMapName = map_store_.GetSelectedMapName();
    if (selectedMapName.empty()) return;

    auto mapDto = map_repo_.LoadMap(selectedMapName);
    if (!mapDto.has_value()) return;

    PopulateStores(*mapDto);
    BindPlayerKeys(*mapDto);

    GameHudConfig config;
    for (const auto &p : mapDto->players) {
        std::string moves = {p.upKey, p.leftKey, p.downKey, p.rightKey};
        config.controls.push_back({p.name, moves, p.bombKey});
    }

    presenter_.PresentGameStart(
        map_store_.Get(),
        wall_store_.GetAll(),
        player_store_.GetAll(),
        ghost_store_.GetAll(),
        door_store_.Get(),
        config
    );
}

void StartGame::PopulateStores(const MapDto &dto) {
    wall_store_.Clear();
    player_store_.Clear();
    ghost_store_.Clear();
    door_store_.Clear();
    map_store_.Set(Map(dto.width, dto.height));

    for (const auto &w : dto.walls) {
        wall_store_.Add(Wall(w.x, w.y, w.type));
    }
    for (const auto &g : dto.ghosts) {
        ghost_store_.Add(Ghost(g.x, g.y));
    }
    if (dto.hasDoor) {
        door_store_.Set(Door(dto.doorPosition.x, dto.doorPosition.y));
    }
    for (const auto &p : dto.players) {
        player_store_.Add(Player(p.name, p.x, p.y, 3));
    }
}

void StartGame::BindPlayerKeys(const MapDto &dto) {
    keybind_service_.ClearDynamicKeys();
    for (size_t i = 0; i < dto.players.size(); ++i) {
        const auto &p = dto.players[i];
        int player_id = static_cast<int>(i);
        keybind_service_.BindDynamicKey(p.upKey, [this, player_id]() { move_player_.Execute(player_id, 0, -1); });
        keybind_service_.BindDynamicKey(p.leftKey, [this, player_id]() { move_player_.Execute(player_id, -1, 0); });
        keybind_service_.BindDynamicKey(p.downKey, [this, player_id]() { move_player_.Execute(player_id, 0, 1); });
        keybind_service_.BindDynamicKey(p.rightKey, [this, player_id]() { move_player_.Execute(player_id, 1, 0); });
        keybind_service_.BindDynamicKey(p.bombKey, [this, player_id]() { place_bomb_.Execute(player_id); });
    }
}