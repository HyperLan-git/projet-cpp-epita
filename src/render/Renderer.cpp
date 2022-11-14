#include "render/Renderer.hpp"

SDL_Texture* img = NULL;
SDL_Rect rect;

Renderer::Renderer(Window& win, unsigned int flags, int idx) {
    this->renderer = SDL_CreateRenderer(win.getWindow(), idx, flags);
    if (!this->renderer)
        throw std::runtime_error("Could not create renderer !");
    img = loadImage("resources/textures/herbe.bmp");
    SDL_QueryTexture(img, NULL, NULL, &rect.w, &rect.h);
}

void Renderer::render(SDL_Surface* surface) {
    SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255);
    SDL_RenderClear(this->renderer);
    SDL_SetRenderDrawColor(this->renderer, 255, 255, 255, 255);
    SDL_RenderCopy(renderer, img, NULL, &rect);
    SDL_SetRenderDrawColor(this->renderer, 0, 255, 255, 255);
    SDL_RenderDrawRect(this->renderer, &rect);
    SDL_RenderPresent(this->renderer);
}

SDL_Texture* Renderer::loadImage(const char* file) {
    return SDL_CreateTextureFromSurface(renderer, SDL_LoadBMP(file));
}

Renderer::~Renderer() { SDL_DestroyRenderer(this->renderer); }