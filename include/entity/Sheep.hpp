#pragma once
#include <cstdlib>
#include <iostream>

class Sheep;

#include "entity/Animal.hpp"

class Sheep : public Animal {
   public:
    Sheep(std::weak_ptr<World> &world, SDL_Rect hitbox, SDL_Texture *texture,
          SDL_Point position);
    virtual void update() override;
};