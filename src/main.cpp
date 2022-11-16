#include <iostream>
#include <string>

#include "game/Game.hpp"

// TODO inline what deserves to be

int main() {
    try {
        Game g;
        g.getWorld()->spawn(std::move(std::make_unique<Animal>(
            SDL_Rect({0, 0, 100, 100}), g.getRenderer()->getTexture("grass"))));
        g.run();
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        std::cerr << "Cause: " << SDL_GetError() << std::endl;
        return -1;
    } catch (std::exception e) {
        std::cerr << e.what() << std::endl;
        return -1;
    }
    return 0;
}