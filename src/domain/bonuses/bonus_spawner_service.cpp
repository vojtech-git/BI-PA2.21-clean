#include "domain/bonuses/bonus_spawner_service.hpp"

#include <cstdlib>

std::optional<BonusType> BonusSpawnerService::RollBonus(const BonusChances &chances) {
    std::vector<BonusType> available = CollectAvailableBonusTypes(chances);
    if (available.empty()) {
        return std::nullopt;
    }

    if (std::rand() % 2 != 0) {
        return std::nullopt;
    }

    return SelectRandomBonus(available);
}

std::vector<BonusType> BonusSpawnerService::CollectAvailableBonusTypes(const BonusChances &chances) {
    std::vector<BonusType> available;
    if (chances.flame)      available.push_back(BonusType::FlameLength);
    if (chances.delay)      available.push_back(BonusType::BombCooldown);
    if (chances.health)     available.push_back(BonusType::Health);
    if (chances.frozen)     available.push_back(BonusType::Freeze);
    if (chances.levitation) available.push_back(BonusType::Levitation);
    return available;
}

BonusType BonusSpawnerService::SelectRandomBonus(const std::vector<BonusType> &available_types) {
    size_t idx = static_cast<size_t>(std::rand()) % available_types.size();
    return available_types[idx];
}