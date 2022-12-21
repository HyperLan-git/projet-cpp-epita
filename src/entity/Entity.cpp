#include "entity/Entity.hpp"

Entity::Entity(std::weak_ptr<World> world) : world(world) {}

bool Entity::isDead() const { return this->dead; }

void Entity::kill() { this->dead = true; }

Entity::~Entity() {}