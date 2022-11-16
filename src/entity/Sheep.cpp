#include "entity/Sheep.hpp"

Sheep::Sheep(SDL_Rect hitbox, SDL_Texture *texture, SDL_Point position)
    : Animal(hitbox, texture, position)
{
    framecount = 10;
}

void Sheep::update()
{
    if (framecount == 100)
    {
        // Random move
        int direction = std::rand() % 4;
        move(direction, 5); // SLOW
    }
    framecount--;
    if (framecount == 0)
        framecount = 100;
}