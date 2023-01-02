#pragma once

class Shepard;

#include "Animal.hpp"
#include "game/InputHandler.hpp"

class Shepard : public Animal {
   public:
    Shepard(std::weak_ptr<World> world, SDL_Rect hitbox, SDL_Texture *texture,
            SDL_Point position, bool male,
            std::weak_ptr<InputHandler> inputHandler);

    virtual void update() override;

    virtual bool isShepard() const override;

   private:
    std::weak_ptr<InputHandler> inputHandler;
};