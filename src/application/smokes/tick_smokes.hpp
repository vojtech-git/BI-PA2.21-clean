#pragma once
#include "application/smokes/smoke_store.hpp"
#include "application/bombs/bomb_presenter.hpp"

class TickSmokes {
public:
    TickSmokes(SmokeStore &smoke_store, BombPresenter &presenter);
    void Execute(float dt);

private:
    SmokeStore &smoke_store_;
    BombPresenter &presenter_;
};