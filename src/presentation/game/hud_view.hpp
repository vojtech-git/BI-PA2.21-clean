#pragma once
#include "curses_wrapper.hpp"
#include <string>
#include <unordered_map>

class HudView {
public:
    HudView() = default;
    ~HudView();

    void InitWindow(int y, int x, int width, int height);
    void Reset();
    void AddPlayerSlot(int player_id, const std::string &name);
    void UpdatePlayer(int player_id, int health, size_t explosion_size, float cd, bool frozen, bool levitating);
    void SetPosition(int y, int x);
    void StageRender();
    void ClearWindow();
    void UpdatePlayerHealth(int player_id, int health);

    int GetHeight() const { return height_; }
    int GetY() const { return y_; }
    int GetX() const { return x_; }

private:
    void ClearField(int y, int x, int width);

    WINDOW *window_{nullptr};
    int y_{0};
    int x_{0};
    int width_{0};
    int height_{0};
    std::unordered_map<int, int> player_slots_;
    int next_slot_{0};
};