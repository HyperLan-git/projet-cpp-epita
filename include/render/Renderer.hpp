#pragma once

class Renderer;

#include <SDL2/SDL.h>
#include <SDL2/SDL_thread.h>

#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <thread>
#include <unordered_map>

#include "Instance.hpp"
#include "game/World.hpp"
#include "render/Window.hpp"

class Renderer : Instance {
   public:
    Renderer(Window& win, unsigned int flags = 0, int idx = -1);

    void render(SDL_Surface* surface, std::unique_ptr<World>& world);

    SDL_Texture* addTexture(const std::string& name, const std::string& bmp);

    SDL_Texture* getTexture(const std::string& bmp);

    ~Renderer();

   private:
    SDL_Renderer* renderer = NULL;
    std::unordered_map<std::string, SDL_Texture*> textures;
};