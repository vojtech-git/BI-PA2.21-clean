#pragma once
#include "curses_wrapper.hpp"
#include <cstddef>
#include <vector>
#include <array>
#include <cstdint>

enum class EntityVisualLayer : size_t {
    Player = 0,
    Ghost,
    Bomb,
    Smoke,
    Bonus,
    Door,
    SoftWall,
    HardWall,
    Count
};

class BoardView {
public:
    BoardView() = default;
    ~BoardView();

    void InitWindow(int y, int x, size_t width, size_t height);
    void Clear();
    void AddEntity(size_t x, size_t y, EntityVisualLayer layer);
    void RemoveEntity(size_t x, size_t y, EntityVisualLayer layer);
    void MoveEntity(size_t old_x, size_t old_y, size_t new_x, size_t new_y, EntityVisualLayer layer);
    void SetPosition(int y, int x);
    void StageRender();
    void ClearWindow();

    char GetTopChar(size_t x, size_t y) const;
    size_t GetWidth() const { return width_; }
    size_t GetHeight() const { return height_; }
    int GetY() const { return y_; }
    int GetX() const { return x_; }

private:
    void UpdateCell(size_t x, size_t y);
    bool IsInBounds(size_t x, size_t y) const;

    using TileLayers = std::array<uint8_t, static_cast<size_t>(EntityVisualLayer::Count)>;
    WINDOW *window_{nullptr};
    int y_{0};
    int x_{0};
    size_t width_{0};
    size_t height_{0};
    std::vector<std::vector<TileLayers>> grid_;
};