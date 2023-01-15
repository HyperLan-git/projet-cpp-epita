#pragma once

class SheperdDog;

#include "Animal.hpp"

class SheperdDog : public Animal {
   public:
    SheperdDog(std::weak_ptr<World> world, SDL_Rect hitbox,
               SDL_Texture *texture, SDL_Point position, bool male);

    virtual void update() override;

    virtual bool isSheperd() const override;
};