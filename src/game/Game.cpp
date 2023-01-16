#include "game/Game.hpp"

#include "entity/Sheep.hpp"
#include "entity/Shepherd.hpp"
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

    int spawn = 1, delay = 1200;
    int counter = 0;
    std::weak_ptr<Entity> shepherd(SPAWN_ENTITY(
        Shepherd, this->world,
        SDL_Rect({world->getWidth() / 2, world->getHeight() / 2, 100, 100}),
        this->renderer->getTexture("shepherd"),
        SDL_Point({world->getWidth() / 2, world->getHeight() / 2}),
        std::rand() % 2, std::weak_ptr<InputHandler>(this->inputHandler)));

    for (int i = 0; i < 2; i++) {
        SDL_Point p = {world->getWidth() / 2,
                       world->getHeight() / 2 - 100 + i * 200};
        SPAWN_ENTITY(ShepherdDog, this->world, SDL_Rect({p.x, p.y, 100, 100}),
                     this->renderer->getTexture("shepherd_dog"), p,
                     std::rand() % 2, shepherd, i == 0 ? WEST : EAST);
    }
    long score = 0;
    int seconds = 90;
    frames = 60 * seconds;
    while (!this->window->shouldClose() && --frames > 0) {
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
        }
        constexpr Entity_pred predSheep = [](std::shared_ptr<Entity>& ptr) {
            return ptr->isSheep();
        };

        score += world->getEntitiesIf(predSheep).size();

        this->world->update();
        this->inputHandler->update();

        this->renderer->render(this->surface, this->world);
    }
    std::cout << "Score final : "
              << (float)((int)((score / (float)(60 * seconds)) * 100)) / 100.f
              << "\nNombre de moutons en moyenne sur la carte." << std::endl;
}

Game::~Game() { SDL_Quit(); }
