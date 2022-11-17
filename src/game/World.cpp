#include "game/World.hpp"

World::World() {}

void World::update() {
    for (auto &e : this->entities) e->update();
    this->entities.erase(
        std::remove_if(this->entities.begin(), this->entities.end(),
                       [](std::unique_ptr<Entity> &e) { return e->isDead(); }),
        this->entities.end());
}

World::~World() {}