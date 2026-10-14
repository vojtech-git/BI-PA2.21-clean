#pragma once

#include "domain/maps/map.hpp"
#include "domain/walls/wall.hpp"
#include "domain/players/player.hpp"
#include "domain/ghosts/ghost.hpp"
#include "domain/doors/door.hpp"
#include "application/games/game_hud_state.hpp"
#include <vector>
#include <optional>

class GamePresenter {
public:
    virtual ~GamePresenter() = default;

    virtual void SetHudConfig(const GameHudConfig &config) = 0;

    virtual void PresentGame(
        const Map &map,
        const std::vector<Wall> &walls,
        const std::vector<Player> &players,
        const std::vector<Ghost> &ghosts,
        const std::optional<Door> &door
    ) = 0;
};