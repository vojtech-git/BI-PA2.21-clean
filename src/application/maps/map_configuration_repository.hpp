#pragma once

#include <vector>
#include <string>
#include <optional>
#include "application/maps/map_dto.hpp"

class MapConfigurationRepository {
public:
    virtual ~MapConfigurationRepository() = default;

    virtual std::vector<std::string> LoadAllMapNames() = 0;
    virtual std::optional<MapDto> LoadMapConfiguration(const std::string &map_name) = 0;
};