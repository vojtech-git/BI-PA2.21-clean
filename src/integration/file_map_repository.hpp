#pragma once

#include "application/maps/map_configuration_repository.hpp"
#include <vector>
#include <string>
#include <optional>

class FileMapRepository : public MapConfigurationRepository {
public:
    std::vector<std::string> LoadAllMapNames() override;
    std::optional<MapDto> LoadMapConfiguration(const std::string &map_name) override;
};