#include "presentation/event_router.hpp"

EventRouter::EventRouter(AppState &app_state, MovePlayer &move_player, PlaceBomb &place_bomb)
    : app_state_(app_state),
      move_player_(move_player),
      place_bomb_(place_bomb) {}

void EventRouter::BindKey(AppState currentState, int key, Action action) {
    key_routes_[{currentState, key}] = std::move(action);
}

void EventRouter::BindPlayerMove(int key, PlayerId player_id, MoveDirection dir) {
    dynamic_routes_[key] = [this, player_id, dir]() {
        switch (dir) {
            case MoveDirection::Up:    move_player_.Execute(player_id, 0, -1); break;
            case MoveDirection::Down:  move_player_.Execute(player_id, 0, 1);  break;
            case MoveDirection::Left:  move_player_.Execute(player_id, -1, 0); break;
            case MoveDirection::Right: move_player_.Execute(player_id, 1, 0);  break;
        }
    };
}

void EventRouter::BindPlayerBomb(int key, PlayerId player_id) {
    dynamic_routes_[key] = [this, player_id]() {
        place_bomb_.Execute(player_id);
    };
}

void EventRouter::ClearDynamicKeys() {
    dynamic_routes_.clear();
}

void EventRouter::dispatchKey(AppState state, int key) {
    if (state == AppState::Game) {
        auto dynamic_it = dynamic_routes_.find(key);
        if (dynamic_it != dynamic_routes_.end()) {
            dynamic_it->second();
            return;
        }
    }
    auto it = key_routes_.find({state, key});
    if (it != key_routes_.end()) {
        it->second();
    }
}

void EventRouter::RegisterTick(AppState state, TickAction action) {
    tick_routes_[state].push_back(std::move(action));
}

void EventRouter::DispatchTick(AppState state, float dt) {
    auto it = tick_routes_.find(state);
    if (it != tick_routes_.end()) {
        for (auto &action : it->second) {
            action(dt);
        }
    }
}