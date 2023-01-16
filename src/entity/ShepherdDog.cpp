#include "entity/ShepherdDog.hpp"

ShepherdDog::ShepherdDog(std::weak_ptr<World> world, SDL_Rect hitbox,
                         SDL_Texture *texture, SDL_Point position, bool male,
                         std::weak_ptr<Entity> shepherd, Direction dir)
    : Animal(world, hitbox, texture, position, male),
      shepherd(shepherd),
      direction(dir),
      dirTimer(500) {
    framecount = 40;
}

SDL_Point getDirectionVector(Direction dir) {
    switch (dir) {
        case NORTH:
            return {0, DOG_DIST};
        case EAST:
            return {DOG_DIST, 0};
        case SOUTH:
            return {0, -DOG_DIST};
        case WEST:
            return {-DOG_DIST, 0};
    }
    return SDL_Point();
}

Direction switchDirection(Direction dir) {
    switch (dir) {
        case NORTH:
            return EAST;
        case EAST:
            return SOUTH;
        case SOUTH:
            return WEST;
        case WEST:
            return NORTH;
    }
    return NORTH;
}

void ShepherdDog::update() {
    if (--dirTimer == 0) {
        dirTimer = 250;
        direction = switchDirection(direction);
    }
    if (shepherd.expired()) return;
    SDL_Point p = std::shared_ptr<Entity>(shepherd)->getPosition(),
              v = getDirectionVector(direction);
    p.x += v.x;
    p.y += v.y;
    chase(p, 2);
    Animal::update();
}

bool ShepherdDog::isShepherd() const { return true; }
