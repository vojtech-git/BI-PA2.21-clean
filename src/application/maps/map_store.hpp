#pragma once
#include "domain/maps/map.hpp"
#include "application/maps/map_dto.hpp"
#include <string>

class MapStore {
public:
    MapStore() = default;
    ~MapStore() = default;

    Map Get() const { return map_; }
    void Set(Map map) { map_ = map; }

    void SetBonusChances(const BonusChances &chances) { bonus_chances_ = chances; }
    const BonusChances& GetBonusChances() const { return bonus_chances_; }

    void SetSelectedMapName(const std::string &name) { selected_map_name_ = name; }
    std::string GetSelectedMapName() const { return selected_map_name_; }

private:
    Map map_{0, 0};
    std::string selected_map_name_{};
    BonusChances bonus_chances_{};
};