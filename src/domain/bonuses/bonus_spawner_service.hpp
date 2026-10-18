#pragma once

#include <optional>
#include <vector>

#include "domain/boards/bonus_chances.hpp"
#include "domain/bonuses/bonus.hpp"

class BonusSpawnerService {
public:
    static std::optional<BonusType> RollBonus(const BonusChances &chances);

private:
    static std::vector<BonusType> CollectAvailableBonusTypes(const BonusChances &chances);
    static BonusType SelectRandomBonus(const std::vector<BonusType> &available_types);
};