#pragma once

class ShepherdDog;

#include "Animal.hpp"

#define DOG_DIST 200

enum Direction { NORTH, EAST, SOUTH, WEST };

class ShepherdDog : public Animal {
   public:
    ShepherdDog(std::weak_ptr<World> world, SDL_Rect hitbox,
                SDL_Texture *texture, SDL_Point position, bool male,
                std::weak_ptr<Entity> shepherd, Direction dir = NORTH);

    virtual void update() override;

    virtual bool isShepherd() const override;

   private:
    Direction direction;
    std::weak_ptr<Entity> shepherd;
    int dirTimer;
};