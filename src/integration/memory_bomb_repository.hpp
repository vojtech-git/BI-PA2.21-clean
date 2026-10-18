#pragma once
#include "integration/memory_repository.hpp"
#include "application/bombs/bomb_repository.hpp"

class MemoryBombRepository 
    : public InMemoryRepository<Bomb, BombId>,
      public BombRepository {};