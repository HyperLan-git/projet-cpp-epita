#include "entity/Entity.hpp"

Entity::Entity() {}

bool Entity::isDead() const { return this->dead; }

void Entity::kill() { this->dead = true; }

Entity::~Entity() {}