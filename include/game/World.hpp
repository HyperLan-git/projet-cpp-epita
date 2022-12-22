#pragma once

class World;

#include <algorithm>
#include <memory>
#include <queue>
#include <vector>

#include "Instance.hpp"
#include "entity/Animal.hpp"

// Note that entities spawned this way will be added on the next logical frame
#define SPAWN_ENTITY(TYPE, WORLD, ...) \
    WORLD->spawn(std::move(            \
        std::make_shared<TYPE>(std::weak_ptr<World>(WORLD), __VA_ARGS__)))

typedef bool (*Entity_pred)(std::shared_ptr<Entity>& entity);

class World : Instance {
   public:
    World(unsigned width, unsigned height);

    void update();

    inline void spawn(std::shared_ptr<Entity>&& entity) {
        toAdd.push_back(entity);
    }

    inline const std::vector<std::shared_ptr<Entity>>& getEntities() const {
        return entities;
    }

    /**
     * @brief DO NOT KEEP THE POINTERS TO ENTITIES IN A MEMBER FIELD,
     * use weak_ptr instead
     *
     * @param predicate a predicate that will be evaluated for every entity
     * @return std::vector<std::shared_ptr<Entity>> a list of pointers to
     * entities that validated the predicate
     */
    std::vector<std::shared_ptr<Entity>> getEntitiesIf(Entity_pred predicate);

    inline const int getWidth() const { return width; }
    inline const int getHeight() const { return height; }

    ~World();

   private:
    inline void spawnNow(std::shared_ptr<Entity>&& entity) {
        entities.push_back(entity);
    }
    std::deque<std::shared_ptr<Entity>> toAdd;
    std::vector<std::shared_ptr<Entity>> entities;
    const unsigned width, height;
};