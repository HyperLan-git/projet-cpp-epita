#include "render/Window.hpp"

#include <iostream>

Window::Window(const char* title, int x, int y, int w, int h, Uint32 flags) {
    this->window = SDL_CreateWindow(title, x, y, w, h, flags);
    if (!this->window) throw std::runtime_error("Could not create window ! ");
    SDL_EventFilter filter = [](void* userdata, SDL_Event* event) {
        if (event->window.event == SDL_WINDOWEVENT_CLOSE) {
            *((bool*)userdata) = true;
        }
        return 0;
    };
    SDL_AddEventWatch(filter, &(this->closed));
}

bool Window::shouldClose() const { return closed; }

int Window::pollEvent(SDL_Event* event) const { return SDL_PollEvent(event); }

void Window::close() { this->closed = true; }

SDL_Surface* Window::getSurface() {
    SDL_Surface* result = SDL_GetWindowSurface(this->window);
    if (!result) throw std::runtime_error("Could not get window surface ! ");
    return result;
}

SDL_Window* Window::getWindow() { return this->window; }