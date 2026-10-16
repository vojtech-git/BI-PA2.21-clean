#include "event_router.hpp"

EventRouter::EventRouter(AppState &app_state)
    : app_state_(app_state) {}

void EventRouter::BindKey(AppState currentState, int key, Action action) {
    key_routes_[{currentState, key}] = std::move(action);
}

void EventRouter::BindDynamicKey(int key, std::function<void()> action) {
    dynamic_routes_[key] = std::move(action);
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