#include "game/Game.hpp"
#include "entity/Sheep.hpp"
#include "entity/Wolf.hpp"

Game::Game()
{
    if (SDL_Init(SDL_INIT_EVERYTHING))
        throw std::runtime_error("Could not init SDL !");
    this->window = std::make_unique<Window>("Projet SDL Partie 1", 0, 0, 640, 480,
                                            SDL_WINDOW_RESIZABLE);
    this->renderer = std::make_unique<Renderer>(
        *window, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    this->world = std::make_unique<World>();
    this->surface = this->window->getSurface();
}

void Game::run()
{
    int spawn = 0;
    while (!this->window->shouldClose())
    {
        SDL_Event ev;
        this->window->pollEvent(&ev);

        if (spawn == 0)
        {
            // SPAWN A RANDOM ANIMAL
            int random = std::rand() % 2;
            int randomX = std::rand() % 540;
            int ranomdY = std::rand() % 380;

            if (random == 0)
            {
                this->world->spawn(std::move(std::make_unique<Sheep>(
                    SDL_Rect({randomX, ranomdY, 100, 100}), this->renderer->getTexture("grass"),
                    SDL_Point({randomX, ranomdY}))));
            }
            if (random == 1)
            {
                this->world->spawn(std::move(std::make_unique<Wolf>(
                    SDL_Rect({randomX, ranomdY, 100, 100}), this->renderer->getTexture("grass"),
                    SDL_Point({randomX, ranomdY}))));
            }
        }
        spawn++;
        if (spawn == 1000)
            spawn = 0;

        this->world->update();

        this->renderer->render(this->surface, this->world);
    }
}

Game::~Game() { SDL_Quit(); }
