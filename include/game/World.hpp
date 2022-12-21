#pragma once

class World;

#include <algorithm>
#include <memory>
#include <vector>

#include "Instance.hpp"
#include "entity/Animal.hpp"

#define SPAWN_ENTITY(TYPE, WORLD, ...)             \
    WORLD->spawn(std::move(std::make_unique<TYPE>( \
        std::weak_ptr<World>(this->world), __VA_ARGS__)))

class World : Instance {
   public:
    World();

    void update();

    inline void spawn(std::unique_ptr<Entity>&& entity) {
        entities.push_back(std::move(entity));
    }

    inline const std::vector<std::unique_ptr<Entity>>& getEntities() const {
        return entities;
    }

    ~World();

   private:
    std::vector<std::unique_ptr<Entity>> entities;
};