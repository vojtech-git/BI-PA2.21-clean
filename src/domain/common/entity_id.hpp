#pragma once
#include <cstdint>
#include <cstddef>
#include <functional>

template <typename EntityTag>
class EntityId {
public:
    constexpr EntityId() : value_(0) {}
    constexpr explicit EntityId(uint32_t value) : value_(value) {}

    constexpr uint32_t GetValue() const { return value_; }

    constexpr bool operator==(const EntityId &other) const { return value_ == other.value_; }
    constexpr bool operator!=(const EntityId &other) const { return value_ != other.value_; }
    constexpr bool operator<(const EntityId &other) const { return value_ < other.value_; }

private:
    uint32_t value_;
};

struct PlayerTag {};
struct GhostTag {};
struct BombTag {};
struct WallTag {};
struct BonusTag {};
struct SmokeTag {};
struct DoorTag {};

using PlayerId = EntityId<PlayerTag>;
using GhostId  = EntityId<GhostTag>;
using BombId   = EntityId<BombTag>;
using WallId   = EntityId<WallTag>;
using BonusId  = EntityId<BonusTag>;
using SmokeId  = EntityId<SmokeTag>;
using DoorId = EntityId<DoorTag>;

namespace std {
    template <typename EntityTag>
    struct hash<EntityId<EntityTag>> {
        size_t operator()(const EntityId<EntityTag> &id) const noexcept {
            return std::hash<uint32_t>()(id.GetValue());
        }
    };
}