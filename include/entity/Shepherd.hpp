#pragma once

class Shepherd;

#include "Animal.hpp"
#include "game/InputHandler.hpp"

class Shepherd : public Animal {
   public:
    Shepherd(std::weak_ptr<World> world, SDL_Rect hitbox, SDL_Texture *texture,
             SDL_Point position, bool male,
             std::weak_ptr<InputHandler> inputHandler);

    virtual void update() override;

    virtual bool isShepherd() const override;

   private:
    std::weak_ptr<InputHandler> inputHandler;
};