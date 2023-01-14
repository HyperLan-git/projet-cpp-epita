#include "entity/Shepard.hpp"

Shepard::Shepard(std::weak_ptr<World> world, SDL_Rect hitbox,
                 SDL_Texture *texture, SDL_Point position, bool male,
                 std::weak_ptr<InputHandler> inputHandler)
    : Animal(world, hitbox, texture, position, male),
      inputHandler(inputHandler) {
    life = 8000;
    framecount = 20;
}

void Shepard::update() {
    if (!inputHandler.expired()) {
        std::shared_ptr<InputHandler> input(inputHandler);
        int speed = 3;
        if (framecount > 0) {
            speed *= 2;
            framecount--;
        }
        if (ISDOWN(input->getStatus(SDLK_UP))) this->position.y -= speed;
        if (ISDOWN(input->getStatus(SDLK_DOWN))) this->position.y += speed;
        if (ISDOWN(input->getStatus(SDLK_RIGHT))) this->position.x += speed;
        if (ISDOWN(input->getStatus(SDLK_LEFT))) this->position.x -= speed;
        SDL_Point mousePos = input->getMousePos();
        if (input->getMouseState() == PRESSED &&
            SDL_PointInRect(&mousePos, &this->hitbox))
            this->framecount = 20;
    }
    Animal::update();
}

bool Shepard::isShepard() const { return true; }