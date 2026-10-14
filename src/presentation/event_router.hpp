#pragma once

#include "presentation/app_state.hpp"
#include "application/input/keybind_service.hpp"
#include <map>
#include <functional>

using Action = std::function<void()>;

class EventRouter : public KeybindService {
public:
    explicit EventRouter(AppState &app_state);
    ~EventRouter() override = default;

    void BindKey(AppState currentState, int key, Action action);
    void dispatchKey(AppState state, int key);

    void BindDynamicKey(int key, std::function<void()> action) override;
    void ClearDynamicKeys() override;

private:
    AppState &app_state_;
    std::map<std::pair<AppState, int>, Action> key_routes_;
    std::map<int, Action> dynamic_routes_;
};