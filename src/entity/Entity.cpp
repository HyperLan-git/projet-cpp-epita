#include "entity/Entity.hpp"

Entity::Entity(std::weak_ptr<World> world, SDL_Point position, bool male)
    : world(world), position(position), male(male) {}

bool Entity::isDead() const { return this->dead; }

void Entity::kill() { this->dead = true; }

void Entity::wander(unsigned speed) {
    this->position.x += (std::rand() % (speed * 2)) - speed;
    this->position.y += (std::rand() % (speed * 2)) - speed;
}

void Entity::chase(const std::shared_ptr<Entity>& other, int speed) {
    int diffX = other->getPosition().x - this->position.x,
        diffY = other->getPosition().y - this->position.y;
    if (diffX == diffY && diffY == 0) {
        if (speed < 0) {
            this->position.x -= std::rand() % speed - 10;
            this->position.y -= std::rand() % speed - 10;
        }
        return;
    }
    int len = std::sqrt(diffX * diffX + diffY * diffY);
    if (len < speed && speed > 0) {
        this->position.x = other->position.x;
        this->position.y = other->position.y;
    } else {
        this->position.x += (diffX * speed) / len;
        this->position.y += (diffY * speed) / len;
    }
}

void Entity::flee(const std::shared_ptr<Entity>& other, int speed) {
    chase(other, -speed);
}

const std::shared_ptr<Entity> Entity::getClosest(
    const std::vector<std::shared_ptr<Entity>>& entities) const {
    unsigned dist = -1;
    std::shared_ptr<Entity> res;
    for (const std::shared_ptr<Entity>& e : entities)
        if (e.get() != this) {
            int dX = position.x - e->getPosition().x,
                dY = position.y - e->getPosition().y;
            unsigned d = dX * dX + dY * dY;
            if (d < dist) {
                res = e;
                dist = d;
            }
        }
    return res;
}

Entity::~Entity() {}