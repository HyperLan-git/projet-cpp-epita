#include "entity/Animal.hpp"

Animal::Animal(std::weak_ptr<World> world, SDL_Rect hitbox,
               SDL_Texture *texture, SDL_Point position, bool male)
    : Entity(world, position, male), hitbox(hitbox), texture(texture) {}

void Animal::draw(SDL_Renderer *renderer) {
    SDL_RenderCopy(renderer, texture, NULL, &hitbox);
}

void Animal::update() {
    if (this->world.expired()) return;
    std::shared_ptr<World> w(this->world);
    int maxX = w->getWidth() - this->hitbox.w / 2,
        maxY = w->getHeight() - this->hitbox.h / 2;
    position.x = std::clamp(position.x, this->hitbox.w / 2, maxX);
    position.y = std::clamp(position.y, this->hitbox.h / 2, maxY);
    hitbox.x = position.x - hitbox.w / 2;
    hitbox.y = position.y - hitbox.h / 2;
}

bool Animal::collidesWith(const std::shared_ptr<Entity> &other) const {
    if (!other) return false;
    SDL_Point pos = other->getPosition();
    return SDL_PointInRect(&pos, &this->hitbox);
}

Animal::~Animal() {}