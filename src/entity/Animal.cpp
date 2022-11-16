#include "entity/Animal.hpp"

Animal::Animal(SDL_Rect hitbox, SDL_Texture *texture, SDL_Point position)
    : hitbox(hitbox), texture(texture), position(position) {}

void Animal::draw(SDL_Renderer *renderer)
{
    SDL_RenderCopy(renderer, texture, NULL, &hitbox);
}

void Animal::update() {}

Animal::~Animal() {}