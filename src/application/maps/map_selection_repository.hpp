#pragma once

#include <string>

class MapSelectionRepository {
public:
    virtual ~MapSelectionRepository() = default;

    virtual void SetSelectedMapName(const std::string &map_name) = 0;
    virtual std::string GetSelectedMapName() const = 0;
};