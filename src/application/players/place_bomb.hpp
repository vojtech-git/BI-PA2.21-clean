#pragma once

#include "application/bombs/bomb_presenter.hpp"
#include "application/bombs/bomb_repository.hpp"
#include "application/common/id_generator_service.hpp"
#include "application/players/player_repository.hpp"
#include "domain/common/entity_id.hpp"

class PlaceBomb {
public:
    PlaceBomb(
        PlayerRepository &player_repo,
        BombRepository &bomb_repo,
        IdGeneratorService &id_generator,
        BombPresenter &presenter
    );

    void Execute(PlayerId player_id);

private:
    PlayerRepository &player_repo_;
    BombRepository &bomb_repo_;
    IdGeneratorService &id_generator_;
    BombPresenter &presenter_;
};