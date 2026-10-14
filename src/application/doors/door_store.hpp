#pragma once
#include "domain/doors/door.hpp"
#include <optional>

class DoorStore {
public:
    DoorStore() = default;
    ~DoorStore() = default;

    std::optional<Door> Get() const { return door_; }
    void Set(const Door &door) { door_ = door; }
    void Clear() { door_ = std::nullopt; }

private:
    std::optional<Door> door_;
};