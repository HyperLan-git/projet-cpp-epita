#include "game/Game.hpp"

#include "entity/Sheep.hpp"
#include "entity/Wolf.hpp"

Game::Game() {
    if (SDL_Init(SDL_INIT_EVERYTHING))
        throw std::runtime_error("Could not init SDL !");
    this->window = std::make_unique<Window>("Projet SDL Partie 2", 0, 0, 2000,
                                            800, SDL_WINDOW_RESIZABLE);
    this->renderer = std::make_unique<Renderer>(
        *window, SDL_RENDERER_ACCELERATED /*| SDL_RENDERER_PRESENTVSYNC*/);
    this->world = std::make_unique<World>(2000, 800);
    this->surface = this->window->getSurface();
}

void Game::run() {
    std::srand(std::time(NULL));
    for (int i = 0; i < 5; i++) {
        int randomX = std::rand() % 1900;
        int randomY = std::rand() % 700;
        for (int j = 0; j < 3; j++) {
            SPAWN_ENTITY(Sheep, this->world,
                         SDL_Rect({randomX, randomY, 100, 100}),
                         this->renderer->getTexture("sheep"),
                         SDL_Point({randomX, randomY}), std::rand() % 2);
            randomX = std::rand() % 1900;
            randomY = std::rand() % 700;
        }
    }

    int spawn = 1, delay = 400;
    int counter = 0;
    while (!this->window->shouldClose()) {
        SDL_Event ev;
        this->window->pollEvent(&ev);

        if (ev.type == SDL_KEYDOWN && ev.key.keysym.sym == SDLK_ESCAPE)
            this->window->close();

        if ((++spawn % delay) == 0) {
            int randomX = std::rand() % 1900;
            int randomY = std::rand() % 700;
            SPAWN_ENTITY(Wolf, this->world,
                         SDL_Rect({randomX, randomY, 100, 100}),
                         this->renderer->getTexture("wolf"),
                         SDL_Point({randomX, randomY}));
            if (delay > 10) delay -= 2;
        }
        if ((++counter % 60) == 0)
            std::cout << "entities : " << this->world->getEntities().size()
                      << std::endl;

        this->world->update();

        this->renderer->render(this->surface, this->world);
    }
}

Game::~Game() { SDL_Quit(); }
