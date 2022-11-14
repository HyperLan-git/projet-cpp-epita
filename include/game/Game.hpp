#pragma once

class Game;

#include "render/Renderer.hpp"
#include "render/Window.hpp"

class Game : Instance {
   public:
    Game();

    void run();

    ~Game();

   private:
    std::unique_ptr<Renderer> renderer;
    std::unique_ptr<Window> window;
    SDL_Surface* surface;
};