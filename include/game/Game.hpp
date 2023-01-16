#pragma once
#include <cstdlib>

class Game;

#include "entity/ShepherdDog.hpp"
#include "game/InputHandler.hpp"
#include "game/World.hpp"
#include "render/Renderer.hpp"
#include "render/Window.hpp"

class Game : Instance {
   public:
    Game();

    void run();

    const std::unique_ptr<Renderer> &getRenderer() const { return renderer; }
    const std::shared_ptr<World> &getWorld() const { return world; }
    const std::unique_ptr<Window> &getWindow() const { return window; }
    std::unique_ptr<Renderer> &getRenderer() { return renderer; }
    std::shared_ptr<World> &getWorld() { return world; }
    std::unique_ptr<Window> &getWindow() { return window; }

    ~Game();

   private:
    std::shared_ptr<World> world;
    std::unique_ptr<Renderer> renderer;
    std::unique_ptr<Window> window;
    std::shared_ptr<InputHandler> inputHandler;
    SDL_Surface *surface;

    int frames;
};