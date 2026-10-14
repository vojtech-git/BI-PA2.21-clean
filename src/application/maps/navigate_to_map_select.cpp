#include "navigate_to_map_select.hpp"

NavigateToMapSelect::NavigateToMapSelect(MapRepository &repo, MapSelectPresenter &presenter)
    : repo_(repo), presenter_(presenter)
{
}

void NavigateToMapSelect::Execute()
{
    auto maps = repo_.LoadAllMapNames();
    presenter_.PresentMapSelect(maps);
}