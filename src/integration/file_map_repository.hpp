#pragma once
#include "application/maps/map_repository.hpp"

class FileMapRepository : public MapRepository
{
public:
    std::vector<std::string> LoadAllMapNames() override;
    std::optional<MapDto> LoadMap(const std::string &mapName) override;
};