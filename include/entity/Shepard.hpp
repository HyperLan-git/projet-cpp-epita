#pragma once

class Shepard;

#include "Entity.hpp"

class Shepard : Entity {
   public:
    Shepard(std::weak_ptr<World> world, SDL_Point position, bool male);
    bool isShepard() const;

   private:
};