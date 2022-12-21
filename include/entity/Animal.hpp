#pragma once

class Animal;

#include <SDL2/SDL.h>

#include "entity/Entity.hpp"

class Animal : public Entity {
   public:
    Animal(std::weak_ptr<World> world, SDL_Rect hitbox, SDL_Texture *texture,
           SDL_Point position);

    virtual void draw(SDL_Renderer *renderer) override;
    virtual void update() override;
    virtual void move(int direction, unsigned speed);

    virtual ~Animal();

   protected:
    SDL_Rect hitbox;
    SDL_Texture *texture;
    SDL_Point position;
    int life;
    int framecount;
};