#include "entity/Wolf.hpp"

Wolf::Wolf(SDL_Rect hitbox, SDL_Texture *texture, SDL_Point position)
    : Animal(hitbox, texture, position)
{
    framecount = 10;
}

void Wolf::update()
{
    if (framecount == 100)
    {
        // Random move
        int direction = std::rand() % 4;
        move(direction, 10); // FAST
    }
    framecount--;
    if (framecount == 0)
        framecount = 100;
}