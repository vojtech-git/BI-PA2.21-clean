#pragma once

#include "application/bombs/bomb_presenter.hpp"
#include "application/smokes/smoke_repository.hpp"

class TickSmokes {
public:
    TickSmokes(SmokeRepository &smoke_repo, BombPresenter &presenter);
    void Execute(float dt);

private:
    SmokeRepository &smoke_repo_;
    BombPresenter &presenter_;
};