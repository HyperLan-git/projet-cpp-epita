#include "entity/Wolf.hpp"

Wolf::Wolf(std::weak_ptr<World> world, SDL_Rect hitbox, SDL_Texture *texture,
           SDL_Point position)
    : Animal(world, hitbox, texture, position) {
    framecount = 10;
    life = 2500;
}

void Wolf::update() {
    if (framecount == 100) {
        // Random move
        int direction = std::rand() % 4;
        move(direction, 10);  // FAST
    }
    if (framecount-- == 0) framecount = 100;

    if (life-- == 0) kill();
}