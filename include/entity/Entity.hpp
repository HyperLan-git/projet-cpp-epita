#pragma once

class Entity;

#include <SDL2/SDL.h>

class Entity {
   public:
    Entity();

    virtual void draw(SDL_Renderer* renderer) = 0;
    virtual void update() = 0;

    bool isDead() const;
    void kill();

    virtual ~Entity();

   private:
    bool dead = false;
};