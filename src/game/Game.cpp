#include "game/Game.hpp"

Game::Game() {
    if (SDL_Init(SDL_INIT_EVERYTHING))
        throw std::runtime_error("Could not init SDL !");
    this->window = std::make_unique<Window>("heheheha", 0, 0, 640, 480,
                                            SDL_WINDOW_RESIZABLE);
    this->renderer = std::make_unique<Renderer>(
        *window, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    this->world = std::make_unique<World>();
    this->surface = this->window->getSurface();
}

void Game::run() {
    while (!this->window->shouldClose()) {
        SDL_Event ev;
        this->window->pollEvent(&ev);

        this->world->update();

        this->renderer->render(this->surface, this->world);
    }
}

Game::~Game() { SDL_Quit(); }
