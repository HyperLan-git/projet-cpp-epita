#include "entity/Sheep.hpp"

Sheep::Sheep(SDL_Rect hitbox, SDL_Texture *texture, SDL_Point position)
    : Animal(hitbox, texture, position) {
    framecount = 10;
    life = 1500;
}

void Sheep::update() {
    if (framecount == 100) {
        // Random move
        int direction = std::rand() % 4;
        move(direction, 5);  // SLOW
    }
    if (framecount-- == 0) framecount = 100;

    if (life-- == 0) kill();
}