#pragma once
#include "map_repository.hpp"
#include "map_select_presenter.hpp"

class NavigateToMapSelect
{
public:
    NavigateToMapSelect(MapRepository &repo, MapSelectPresenter &presenter);
    void Execute();

private:
    MapRepository &repo_;
    MapSelectPresenter &presenter_;
};