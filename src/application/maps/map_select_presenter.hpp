#pragma once
#include <vector>
#include <string>

class MapSelectPresenter {
public:
    virtual ~MapSelectPresenter() = default;
    virtual void PresentMapSelect(const std::vector<std::string> &maps) = 0;
    virtual void PresentSelectedMap(const std::string &mapName) = 0;
};