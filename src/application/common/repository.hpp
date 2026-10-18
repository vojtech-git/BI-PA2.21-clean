#pragma once
#include <vector>
#include <optional>

template <typename Entity, typename IdType>
class IRepository {
public:
    virtual ~IRepository() = default;

    virtual std::optional<Entity> GetById(IdType id) const = 0;
    virtual std::vector<Entity> GetAll() const = 0;
    virtual void Save(const Entity &entity) = 0;
    virtual bool DeleteById(IdType id) = 0;
    virtual void Clear() = 0;
};