#include "game/Game.hpp"

#include "entity/Sheep.hpp"
#include "entity/Sheperd.hpp"
#include "entity/Wolf.hpp"

Game::Game() {
    if (SDL_Init(SDL_INIT_EVERYTHING))
        throw std::runtime_error("Could not init SDL !");
    this->window = std::make_unique<Window>("Projet SDL Partie 2", 0, 0, 1200,
                                            800, SDL_WINDOW_RESIZABLE);
    this->renderer = std::make_unique<Renderer>(
        *window, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    this->world = std::make_shared<World>(1200, 800);
    this->surface = this->window->getSurface();
    this->inputHandler = std::make_shared<InputHandler>();
}

void Game::run() {
    std::srand(std::time(NULL));
    for (int i = 0; i < 4; i++) {
        int randomX = std::rand() % 1100;
        int randomY = std::rand() % 700;
        SPAWN_ENTITY(Sheep, this->world, SDL_Rect({randomX, randomY, 100, 100}),
                     this->renderer->getTexture("sheep"),
                     SDL_Point({randomX, randomY}), std::rand() % 2);
    }

    int spawn = 1, delay = 500;
    int counter = 0;
    SPAWN_ENTITY(Sheperd, this->world, SDL_Rect({0, 0, 100, 100}),
                 this->renderer->getTexture("shepherd"), SDL_Point(),
                 std::rand() % 2,
                 std::weak_ptr<InputHandler>(this->inputHandler));
    while (!this->window->shouldClose()) {
        SDL_Event ev;
        while (this->window->pollEvent(&ev)) {
            if (ev.type == SDL_KEYDOWN && ev.key.keysym.sym == SDLK_ESCAPE)
                this->window->close();
            this->inputHandler->inputEvent(ev);
        }

        if ((++spawn % delay) == 0) {
            int randomX = std::rand() % 1100;
            int randomY = std::rand() % 700;
            SPAWN_ENTITY(Wolf, this->world,
                         SDL_Rect({randomX, randomY, 100, 100}),
                         this->renderer->getTexture("wolf"),
                         SDL_Point({randomX, randomY}));
            if (delay > 10) delay -= 4;
        }

        this->world->update();
        this->inputHandler->update();

        this->renderer->render(this->surface, this->world);
    }
}

Game::~Game() { SDL_Quit(); }
