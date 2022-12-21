#pragma once

class Entity;

#include <SDL2/SDL.h>

#include <memory>

class World;

class Entity {
   public:
    Entity(std::weak_ptr<World> world);

    virtual void draw(SDL_Renderer* renderer) = 0;
    virtual void update() = 0;

    bool isDead() const;
    void kill();

    virtual ~Entity();

   private:
    bool dead = false;
    std::weak_ptr<World> world;
};

#include "game/World.hpp"
