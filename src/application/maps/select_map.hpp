#pragma once
#include "map_store.hpp"
#include "map_select_presenter.hpp"
#include <string>

class SelectMap {
public:
    SelectMap(MapStore &store, MapSelectPresenter &presenter);
    void Execute(const std::string &mapName);

private:
    MapStore &store_;
    MapSelectPresenter &presenter_;
};