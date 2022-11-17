#include "render/Renderer.hpp"

SDL_Rect rect;

Renderer::Renderer(Window &win, unsigned int flags, int idx)
{
    this->renderer = SDL_CreateRenderer(win.getWindow(), idx, flags);
    if (!this->renderer)
        throw std::runtime_error("Could not create renderer !");
    SDL_Texture *tex = addTexture("grass", "resources/textures/grass.bmp");
    addTexture("sheep", "resources/textures/sheep.bmp");
    addTexture("wolf", "resources/textures/wolf.bmp");
    SDL_QueryTexture(tex, NULL, NULL, &rect.w, &rect.h);
}

void Renderer::render(SDL_Surface *surface, std::unique_ptr<World> &world)
{
    SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255);
    SDL_RenderClear(this->renderer);
    SDL_SetRenderDrawColor(this->renderer, 255, 255, 255, 255);
    for (auto &e : world->getEntities())
        e->draw(this->renderer);
    SDL_RenderPresent(this->renderer);
}

SDL_Texture *Renderer::addTexture(const std::string &name,
                                  const std::string &bmp)
{
    SDL_Texture *tex =
        SDL_CreateTextureFromSurface(renderer, SDL_LoadBMP(bmp.c_str()));
    this->textures.emplace(name, tex);
    return tex;
}

SDL_Texture *Renderer::getTexture(const std::string &name)
{
    return this->textures[name];
}

Renderer::~Renderer()
{
    for (auto &iter : this->textures)
        SDL_DestroyTexture(iter.second);
    SDL_DestroyRenderer(this->renderer);
}