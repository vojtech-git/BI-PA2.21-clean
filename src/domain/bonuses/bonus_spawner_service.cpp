#include "domain/bonuses/bonus_spawner_service.hpp"
#include <cstdlib>

std::optional<BonusType> BonusSpawnerService::RollBonus(const Board &board) {
    std::vector<BonusType> available = CollectAvailableBonusTypes(board);
    if (available.empty()) {
        return std::nullopt;
    }

    if (std::rand() % 2 != 0) {
        return std::nullopt;
    }

    return SelectRandomBonus(available);
}

std::vector<BonusType> BonusSpawnerService::CollectAvailableBonusTypes(const Board &board) {
    std::vector<BonusType> available;
    if (board.HasFlameChance())      available.push_back(BonusType::FlameLength);
    if (board.HasDelayChance())      available.push_back(BonusType::BombCooldown);
    if (board.HasHealthChance())     available.push_back(BonusType::Health);
    if (board.HasFrozenChance())     available.push_back(BonusType::Freeze);
    if (board.HasLevitationChance()) available.push_back(BonusType::Levitation);
    return available;
}

BonusType BonusSpawnerService::SelectRandomBonus(const std::vector<BonusType> &available_types) {
    size_t idx = static_cast<size_t>(std::rand()) % available_types.size();
    return available_types[idx];
}