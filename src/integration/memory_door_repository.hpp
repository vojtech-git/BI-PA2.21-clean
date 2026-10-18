#pragma once

#include "application/doors/door_repository.hpp"

class MemoryDoorRepository : public DoorRepository {
public:
    std::optional<Door> Get() const override {
        return door_;
    }

    void Save(const Door &door) override {
        door_ = door;
    }

    void Clear() override {
        door_ = std::nullopt;
    }

private:
    std::optional<Door> door_{std::nullopt};
};