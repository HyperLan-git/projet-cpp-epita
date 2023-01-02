#pragma once

class InputHandler;

#include <SDL2/SDL.h>

#include <map>

#include "Instance.hpp"
enum KeyStatus { NONE, PRESSED, DOWN, RELEASED };

#define ISDOWN(status) (status == PRESSED || status == DOWN)

class InputHandler : Instance {
   public:
    InputHandler();

    void inputEvent(SDL_Event& ev);
    void update();

    SDL_Point getMousePos() const;
    KeyStatus getMouseState() const;
    KeyStatus getStatus(SDL_KeyCode key) const;

   private:
    std::map<int, KeyStatus> keys;
    int mouseX = -1, mouseY = -1;
    KeyStatus click = NONE;
};