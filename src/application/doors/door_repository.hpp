#pragma once

#include <optional>
#include "domain/doors/door.hpp"

class DoorRepository {
public:
    virtual ~DoorRepository() = default;

    virtual std::optional<Door> Get() const = 0;
    virtual void Save(const Door &door) = 0;
    virtual void Clear() = 0;
};