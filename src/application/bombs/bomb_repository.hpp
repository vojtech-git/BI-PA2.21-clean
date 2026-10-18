#pragma once
#include "application/common/repository.hpp"
#include "domain/bombs/bomb.hpp"

class BombRepository : public virtual IRepository<Bomb, BombId> {};