#pragma once
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

class GameBoardBuffer {
public:
    GameBoardBuffer() = default;

    void Resize(size_t width, size_t height);
    void Clear();

    void AddEntity(size_t x, size_t y, EntityVisualLayer layer);
    void RemoveEntity(size_t x, size_t y, EntityVisualLayer layer);
    void MoveEntity(size_t old_x, size_t old_y, size_t new_x, size_t new_y, EntityVisualLayer layer);

    char GetTopChar(size_t x, size_t y) const;
    size_t GetWidth() const;
    size_t GetHeight() const;

private:
    bool IsInBounds(size_t x, size_t y) const;

    using TileLayers = std::array<uint8_t, static_cast<size_t>(EntityVisualLayer::Count)>;

    size_t width_{0};
    size_t height_{0};
    std::vector<std::vector<TileLayers>> grid_;
};