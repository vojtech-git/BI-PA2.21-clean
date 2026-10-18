#pragma once
#include "integration/memory_repository.hpp"
#include "application/ghosts/ghost_repository.hpp"

class MemoryGhostRepository 
    : public InMemoryRepository<Ghost, GhostId>,
      public GhostRepository {};