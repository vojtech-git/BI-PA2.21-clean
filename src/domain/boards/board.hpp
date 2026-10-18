#pragma once

#include <cstdint>
#include "domain/common/position.hpp"

class Board {
public:
    Board(
        uint32_t width,
        uint32_t height,
        bool flame_chance,
        bool frozen_chance,
        bool levitation_chance,
        bool delay_chance,
        bool health_chance
    );

    uint32_t GetWidth() const;
    uint32_t GetHeight() const;
    bool IsInBounds(Position position) const;

    bool HasFlameChance() const;
    bool HasFrozenChance() const;
    bool HasLevitationChance() const;
    bool HasDelayChance() const;
    bool HasHealthChance() const;

    float GetElapsedTime() const;
    bool IsGameOver() const;
    void UpdateTimer(float dt);
    void MarkGameOver();

private:
    uint32_t width_;
    uint32_t height_;
    bool flame_chance_{false};
    bool frozen_chance_{false};
    bool levitation_chance_{false};
    bool delay_chance_{false};
    bool health_chance_{false};
    float elapsed_time_{0.0f};
    bool is_game_over_{false};
};