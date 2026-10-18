#pragma once
#include "application/common/repository.hpp"
#include <unordered_map>
#include <vector>
#include <optional>

template <typename Entity, typename IdType>
class InMemoryRepository : public virtual IRepository<Entity, IdType> {
public:
    std::optional<Entity> GetById(IdType id) const override {
        auto it = entities_.find(id);
        if (it != entities_.end()) {
            return it->second;
        }
        return std::nullopt;
    }

    std::vector<Entity> GetAll() const override {
        std::vector<Entity> result;
        result.reserve(entities_.size());
        for (const auto &[id, entity] : entities_) {
            result.push_back(entity);
        }
        return result;
    }

    void Save(const Entity &entity) override {
        entities_.insert_or_assign(entity.GetId(), entity);
    }

    bool DeleteById(IdType id) override {
        return entities_.erase(id) > 0;
    }

    void Clear() override {
        entities_.clear();
    }

protected:
    std::unordered_map<IdType, Entity> entities_;
};