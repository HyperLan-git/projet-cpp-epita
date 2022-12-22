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
    int maxX = w->getWidth() - this->hitbox.w,
        maxY = w->getHeight() - this->hitbox.h;
    position.x = std::clamp(position.x, 0, maxX);
    position.y = std::clamp(position.y, 0, maxY);
    hitbox.x = position.x;
    hitbox.y = position.y;
}

bool Animal::collidesWith(const std::shared_ptr<Entity> &other) const {
    if (!other) return false;
    SDL_Point pos = other->getPosition();
    return SDL_PointInRect(&pos, &this->hitbox);
}

void Animal::move(int direction, unsigned speed) {
    switch (direction) {
        case 0:  // UP
            position.y -= speed;
            break;
        case 1:  // DOWN
            position.y += speed;
            break;
        case 2:  // LEFT
            position.x -= speed;
            break;
        case 3:  // RIGHT
            position.x += speed;
            break;
    }
}

Animal::~Animal() {}