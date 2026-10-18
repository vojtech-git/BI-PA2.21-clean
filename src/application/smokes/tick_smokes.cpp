#include "application/smokes/tick_smokes.hpp"

TickSmokes::TickSmokes(SmokeRepository &smoke_repo, BombPresenter &presenter)
    : smoke_repo_(smoke_repo),
      presenter_(presenter) {}

void TickSmokes::Execute(float dt) {
    auto smokes = smoke_repo_.GetAll();

    for (auto &smoke : smokes) {
        smoke.Update(dt);

        if (smoke.IsExpired()) {
            presenter_.PresentSmokeRemoved(smoke.GetX(), smoke.GetY());
            smoke_repo_.DeleteById(smoke.GetId());
        } else {
            smoke_repo_.Save(smoke);
        }
    }
}