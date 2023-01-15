#include "entity/SheperdDog.hpp"

SheperdDog::SheperdDog(std::weak_ptr<World> world, SDL_Rect hitbox,
                       SDL_Texture *texture, SDL_Point position, bool male)
    : Animal(world, hitbox, texture, position, male) {}

void SheperdDog::update() { Animal::update(); }

bool SheperdDog::isSheperd() const { return true; }
