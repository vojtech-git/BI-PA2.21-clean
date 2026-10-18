#pragma once

#include <map>
#include <functional>
#include "presentation/app_state.hpp"
#include "application/input/keybind_service.hpp"
#include "application/players/move_player.hpp"
#include "application/players/place_bomb.hpp"

using Action = std::function<void()>;
using TickAction = std::function<void(float)>;

class EventRouter : public KeybindService {
public:
    EventRouter(AppState &app_state, MovePlayer &move_player, PlaceBomb &place_bomb);
    ~EventRouter() override = default;

    void BindKey(AppState currentState, int key, Action action);
    void dispatchKey(AppState state, int key);
    void RegisterTick(AppState state, TickAction action);
    void DispatchTick(AppState state, float dt);

    void BindPlayerMove(int key, PlayerId player_id, MoveDirection dir) override;
    void BindPlayerBomb(int key, PlayerId player_id) override;
    void ClearDynamicKeys() override;

private:
    AppState &app_state_;
    MovePlayer &move_player_;
    PlaceBomb &place_bomb_;
    std::map<std::pair<AppState, int>, Action> key_routes_;
    std::map<int, Action> dynamic_routes_;
    std::map<AppState, std::vector<TickAction>> tick_routes_;
};