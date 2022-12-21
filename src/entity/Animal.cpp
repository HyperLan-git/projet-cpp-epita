#include "entity/Animal.hpp"

Animal::Animal(std::weak_ptr<World> &world, SDL_Rect hitbox,
               SDL_Texture *texture, SDL_Point position)
    : Entity(world), hitbox(hitbox), texture(texture), position(position) {}

void Animal::draw(SDL_Renderer *renderer) {
    SDL_RenderCopy(renderer, texture, NULL, &hitbox);
}

void Animal::update() {}

void Animal::move(int direction, unsigned speed) {
    switch (direction) {
        case 0:  // UP
            position.y -= speed * 2;
            break;
        case 1:  // DOWN
            position.y += speed * 2;
            break;
        case 2:  // LEFT
            position.x -= speed * 2;
            break;
        case 3:  // RIGHT
            position.x += speed * 2;
            break;
    }
    if (position.x < 0) position.x = 0;
    if (position.y < 0) position.y = 0;
    if (position.x >= 540) position.x = 540;
    if (position.y >= 380) position.y = 380;
    hitbox.x = position.x;
    hitbox.y = position.y;
}

Animal::~Animal() {}