#pragma once

class World;

#include <algorithm>
#include <memory>
#include <vector>

#include "Instance.hpp"
#include "entity/Animal.hpp"

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