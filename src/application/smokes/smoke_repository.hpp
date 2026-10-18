#pragma once
#include "application/common/repository.hpp"
#include "domain/smokes/smoke.hpp"

class SmokeRepository : public virtual IRepository<Smoke, SmokeId> {};