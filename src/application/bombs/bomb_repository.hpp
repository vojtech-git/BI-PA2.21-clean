#pragma once
#include "application/common/repository.hpp"
#include "domain/bombs/bomb.hpp"

class BombRepository : public IRepository<Bomb, BombId> {};