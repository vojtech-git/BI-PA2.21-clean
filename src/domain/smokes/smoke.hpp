#pragma once
#include <cstdint>
#include "domain/common/entity_id.hpp"
#include "domain/common/position.hpp"

class Smoke {
public:
    Smoke(SmokeId id, Position position, uint32_t size);

    SmokeId GetId() const;
    Position GetPosition() const;
    uint32_t GetX() const;
    uint32_t GetY() const;
    uint32_t GetSize() const;
    bool IsExpired() const;

    void Update(float dt);

private:
    SmokeId id_;
    Position position_;
    float smoke_timer_{0.0f};
    uint32_t size_;
};