#pragma once
#include "domain/boards/board.hpp"
#include "domain/walls/wall.hpp"
#include "domain/players/player.hpp"
#include "domain/ghosts/ghost.hpp"
#include "domain/doors/door.hpp"
#include "application/games/game_hud_state.hpp"
#include <vector>
#include <optional>

class GameStartPresenter {
public:
    virtual ~GameStartPresenter() = default;
    virtual void PresentGameStart(
        const Board &board,
        const std::vector<Wall> &walls,
        const std::vector<Player> &players,
        const std::vector<Ghost> &ghosts,
        const std::optional<Door> &door,
        const GameHudConfig &hud_config
    ) = 0;
};