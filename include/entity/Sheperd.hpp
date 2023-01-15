#pragma once

class Sheperd;

#include "Animal.hpp"
#include "game/InputHandler.hpp"

class Sheperd : public Animal {
   public:
    Sheperd(std::weak_ptr<World> world, SDL_Rect hitbox, SDL_Texture *texture,
            SDL_Point position, bool male,
            std::weak_ptr<InputHandler> inputHandler);

    virtual void update() override;

    virtual bool isSheperd() const override;

   private:
    std::weak_ptr<InputHandler> inputHandler;
};