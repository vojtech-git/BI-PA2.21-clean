#include "application/players/place_bomb.hpp"
#include "domain/bombs/bomb.hpp"

PlaceBomb::PlaceBomb(
    PlayerRepository &player_repo,
    BombRepository &bomb_repo,
    IdGeneratorService &id_generator,
    BombPresenter &presenter
) : player_repo_(player_repo),
    bomb_repo_(bomb_repo),
    id_generator_(id_generator),
    presenter_(presenter) {}

void PlaceBomb::Execute(PlayerId player_id) {
    auto player_opt = player_repo_.GetById(player_id);
    if (!player_opt.has_value()) {
        return;
    }

    Player player = *player_opt;
    if (!player.CanPlantBomb()) {
        return;
    }

    Position pos = player.GetPosition();

    for (const auto &b : bomb_repo_.GetAll()) {
        if (b.GetPosition() == pos) {
            return;
        }
    }

    BombId bomb_id = id_generator_.Next<BombId>();
    bomb_repo_.Save(Bomb(bomb_id, pos, player.GetExplosionSize()));

    player.PlantBomb();
    player_repo_.Save(player);

    presenter_.PresentBombPlaced(pos.x, pos.y);
}