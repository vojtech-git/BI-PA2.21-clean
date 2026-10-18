#pragma once

#include <optional>
#include <vector>
#include "domain/boards/board.hpp"
#include "domain/bonuses/bonus.hpp"

class BonusSpawnerService {
public:
    static std::optional<BonusType> RollBonus(const Board &board);

private:
    static std::vector<BonusType> CollectAvailableBonusTypes(const Board &board);
    static BonusType SelectRandomBonus(const std::vector<BonusType> &available_types);
};