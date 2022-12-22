#include "game/World.hpp"

World::World(unsigned width, unsigned height) : width(width), height(height) {}

void World::update() {
    while (!toAdd.empty()) {
        auto &elem = toAdd.back();
        spawnNow(std::move(elem));
        toAdd.pop_back();
    }
    for (auto &e : this->entities) e->update();
    constexpr bool (*dead)(std::shared_ptr<Entity> &) =
        [](std::shared_ptr<Entity> &e) { return e->isDead(); };
    this->entities.erase(
        std::remove_if(this->entities.begin(), this->entities.end(), dead),
        this->entities.end());
}

std::vector<std::shared_ptr<Entity>> World::getEntitiesIf(
    Entity_pred predicate) {
    std::vector<std::shared_ptr<Entity>> result(this->entities);
    std::copy_if(this->entities.begin(), this->entities.end(), result.begin(),
                 predicate);
    return result;
}

World::~World() {}