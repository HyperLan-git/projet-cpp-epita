#pragma once

class Renderer;

#include <SDL2/SDL.h>
#include <SDL2/SDL_thread.h>

#include <iostream>
#include <memory>
#include <stdexcept>
#include <thread>

#include "Instance.hpp"
#include "render/Window.hpp"

class Renderer : Instance {
   public:
    Renderer(Window& win, unsigned int flags = 0, int idx = -1);

    void render(SDL_Surface* surface);

    SDL_Texture* loadImage(const char* file);

    ~Renderer();

   private:
    SDL_Renderer* renderer = NULL;
};