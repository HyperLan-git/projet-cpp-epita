#pragma once

class Sheep;

#include "entity/Animal.hpp"

class Sheep : public Animal {
   public:
    Sheep(std::weak_ptr<World> world, SDL_Rect hitbox, SDL_Texture *texture,
          SDL_Point position, bool male);
    virtual void update() override;
    virtual bool isPrey() const override;
    virtual bool isSheep() const override;

   private:
    int luvTimer = 300;
    std::weak_ptr<Entity> loved;
};