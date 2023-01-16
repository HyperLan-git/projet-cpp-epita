#include "render/Renderer.hpp"

Renderer::Renderer(Window &win, unsigned int flags, int idx) {
    this->renderer = SDL_CreateRenderer(win.getWindow(), idx, flags);
    if (!this->renderer)
        throw std::runtime_error("Could not create renderer !");
    addTexture("grass", "resources/textures/grass.bmp");
    addTexture("sheep", "resources/textures/sheep.bmp");
    addTexture("wolf", "resources/textures/wolf.bmp");
    addTexture("shepherd_dog", "resources/textures/dog.bmp");
    addTexture("shepherd", "resources/textures/shepherd.bmp");
}

#define GRASS_SIZE 100

void Renderer::render(SDL_Surface *surface, std::shared_ptr<World> &world) {
    SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255);
    SDL_RenderClear(this->renderer);
    SDL_SetRenderDrawColor(this->renderer, 255, 255, 255, 255);
    SDL_Texture *grass = this->textures["grass"];
    for (int x = 0; x < world->getWidth(); x += GRASS_SIZE)
        for (int y = 0; y < world->getHeight(); y += GRASS_SIZE) {
            SDL_Rect rect({x, y, GRASS_SIZE, GRASS_SIZE});
            SDL_RenderCopy(this->renderer, grass, NULL, &rect);
        }
    for (auto &e : world->getEntities()) e->draw(this->renderer);
    SDL_RenderPresent(this->renderer);
}

SDL_Texture *Renderer::addTexture(const std::string &name,
                                  const std::string &bmp) {
    auto image = SDL_LoadBMP(bmp.c_str());
    SDL_Texture *tex = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);
    this->textures.emplace(name, tex);
    return tex;
}

SDL_Texture *Renderer::getTexture(const std::string &name) {
    return this->textures[name];
}

Renderer::~Renderer() {
    for (auto &iter : this->textures) SDL_DestroyTexture(iter.second);
    SDL_DestroyRenderer(this->renderer);
}