#include "entity/Shepard.hpp"

Shepard::Shepard(std::weak_ptr<World> world, SDL_Rect hitbox,
                 SDL_Texture *texture, SDL_Point position, bool male,
                 std::weak_ptr<InputHandler> inputHandler)
    : Animal(world, hitbox, texture, position, male),
      inputHandler(inputHandler) {
    life = 8000;
    framecount = 10;
}

void Shepard::update() {
    if (!inputHandler.expired()) {
        std::shared_ptr<InputHandler> input(inputHandler);
        if (ISDOWN(input->getStatus(SDLK_UP))) this->position.y -= 3;
        if (ISDOWN(input->getStatus(SDLK_DOWN))) this->position.y += 3;
        if (ISDOWN(input->getStatus(SDLK_RIGHT))) this->position.x += 3;
        if (ISDOWN(input->getStatus(SDLK_LEFT))) this->position.x -= 3;
    }
    Animal::update();
}

bool Shepard::isShepard() const { return true; }