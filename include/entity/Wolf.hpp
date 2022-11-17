#pragma once
#include <cstdlib>
#include <iostream>

class Wolf;

#include "entity/Animal.hpp"

class Wolf : public Animal
{
public:
    Wolf(SDL_Rect hitbox, SDL_Texture *texture, SDL_Point position);
    virtual void update() override;
};