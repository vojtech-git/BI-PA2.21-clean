#include "select_map.hpp"

SelectMap::SelectMap(MapStore &store, MapSelectPresenter &presenter)
    : store_(store), presenter_(presenter) {}

void SelectMap::Execute(const std::string &mapName) {
    store_.SetSelectedMapName(mapName);
    presenter_.PresentSelectedMap(mapName);
}