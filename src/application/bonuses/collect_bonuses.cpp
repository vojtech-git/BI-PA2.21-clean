#include "collect_bonuses.hpp"

CollectBonuses::CollectBonuses(
    PlayerStore &player_store,
    BonusStore &bonus_store,
    BonusPresenter &presenter
) : player_store_(player_store),
    bonus_store_(bonus_store),
    presenter_(presenter) {}

void CollectBonuses::Execute(int player_id) {
    Player *player = player_store_.GetById(player_id);
    if (!player || player->IsDead()) return;

    size_t px = player->GetX();
    size_t py = player->GetY();

    Bonus collected_bonus(0, 0, BonusType::Health);
    if (bonus_store_.RemoveAt(px, py, &collected_bonus)) {
        ApplyBonus(*player, collected_bonus.GetType());
        presenter_.PresentBonusCollected(px, py);
        presenter_.PresentPlayerStatsUpdated(
            player_id,
            player->GetHealth(),
            player->GetExplosionSize(),
            player->GetBombCooldown(),
            player->isFrozen(),
            player->isLevitating()
        );
    }
}

void CollectBonuses::ApplyBonus(Player &player, BonusType type) {
    switch (type) {
        case BonusType::FlameLength:
            player.AddExplosionSize();
            break;
        case BonusType::BombCooldown:
            player.ReduceBombCooldown(0.3f);
            break;
        case BonusType::Health:
            player.AddHealth(1);
            break;
        case BonusType::Freeze:
            player.Freeze(3.0f);
            break;
        case BonusType::Levitation:
            player.Levitate(5.0f);
            break;
    }
}