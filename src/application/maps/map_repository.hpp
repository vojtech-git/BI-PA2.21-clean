#pragma once
#include <vector>
#include <string>
#include <optional>
#include "map_dto.hpp"

class MapRepository {
public:
    virtual ~MapRepository() = default;
    virtual std::vector<std::string> LoadAllMapNames() = 0;
    virtual std::optional<MapDto> LoadMap(const std::string &mapName) = 0;
};