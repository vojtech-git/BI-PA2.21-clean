#pragma once

#include "domain/bonuses/bonus.hpp"
#include "application/maps/map_dto.hpp"
#include <optional>
#include <vector>

class BonusSpawnerService {
public:
    static std::optional<BonusType> RollBonus(const BonusChances &chances);

private:
    static std::vector<BonusType> CollectAvailableBonusTypes(const BonusChances &chances);
    static BonusType SelectRandomBonus(const std::vector<BonusType> &available_types);
};