#pragma once
#include "integration/memory_repository.hpp"
#include "application/smokes/smoke_repository.hpp"

class MemorySmokeRepository 
    : public InMemoryRepository<Smoke, SmokeId>,
      public SmokeRepository {};