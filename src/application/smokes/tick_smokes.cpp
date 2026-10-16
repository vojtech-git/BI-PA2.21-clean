#include "tick_smokes.hpp"

TickSmokes::TickSmokes(SmokeStore &smoke_store, BombPresenter &presenter)
    : smoke_store_(smoke_store),
      presenter_(presenter) {}

void TickSmokes::Execute(float dt) {
    auto &smokes = smoke_store_.GetAllMutable();
    if (smokes.empty()) return;

    for (size_t i = smokes.size(); i > 0; --i) {
        size_t idx = i - 1;
        smokes[idx].Update(dt);

        if (smokes[idx].IsExpired()) {
            presenter_.PresentSmokeRemoved(smokes[idx].GetX(), smokes[idx].GetY());
            smoke_store_.Remove(idx);
        }
    }
}