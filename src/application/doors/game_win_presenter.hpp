#pragma once
#include <string>

class GameWinPresenter {
public:
    virtual ~GameWinPresenter() = default;
    virtual void PresentDoorRevealed(size_t x, size_t y) = 0;
    virtual void PresentGameWon(const std::string &winner_name, int score_seconds) = 0;
};