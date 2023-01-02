#pragma once

class ShepardDog;

#include "Animal.hpp"

class ShepardDog : public Animal {
   public:
    ShepardDog(std::weak_ptr<World> world, SDL_Rect hitbox,
               SDL_Texture *texture, SDL_Point position, bool male);

    virtual void update() override;

    virtual bool isShepard() const override;
};