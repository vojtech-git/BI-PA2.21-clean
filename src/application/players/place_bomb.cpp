#include "place_bomb.hpp"

PlaceBomb::PlaceBomb(
    PlayerStore &player_store,
    BombStore &bomb_store,
    BombPresenter &presenter
) : player_store_(player_store),
    bomb_store_(bomb_store),
    presenter_(presenter) {}

void PlaceBomb::Execute(int player_id) {
    Player *player = player_store_.GetById(player_id);
    if (!player || player->IsDead() || player->isFrozen() || player->GetBombCooldown() > 0.0f) {
        return;
    }

    size_t x = player->GetX();
    size_t y = player->GetY();

    for (const auto &b : bomb_store_.GetAll()) {
        if (b.GetX() == x && b.GetY() == y) {
            return;
        }
    }

    bomb_store_.Add(Bomb(x, y, player->GetExplosionSize()));
    player->PlantBomb();
    presenter_.PresentBombPlaced(x, y);
}