#pragma once

#include <cstdint>
#include <unordered_map>
#include <typeindex>
#include "domain/common/entity_id.hpp"

class IdGeneratorService {
public:
    virtual ~IdGeneratorService() = default;

    template <typename EntityIdType>
    EntityIdType Next() {
        return EntityIdType(GenerateNextValue(typeid(EntityIdType)));
    }

    template <typename EntityIdType>
    void Reset() {
        ResetValue(typeid(EntityIdType));
    }

    virtual void ResetAll() = 0;

protected:
    virtual uint32_t GenerateNextValue(std::type_index type) = 0;
    virtual void ResetValue(std::type_index type) = 0;
};