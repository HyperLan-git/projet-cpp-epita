#pragma once

class Window;

#include <SDL2/SDL.h>

#include <stdexcept>

#include "Instance.hpp"

class Window : Instance {
   public:
    Window(const char* title, int x, int y, int w, int h, Uint32 flags);

    bool shouldClose() const;

    int pollEvent(SDL_Event* event = NULL) const;

    SDL_Surface* getSurface();
    SDL_Window* getWindow();

   private:
    SDL_Window* window;
    bool closed = false;
};