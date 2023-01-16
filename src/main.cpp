#include <iostream>
#include <string>

#include "game/Game.hpp"

int main() {
    try {
        Game g;
        g.run();
    } catch (const std::runtime_error &e) {
        std::cerr << e.what() << std::endl;
        std::cerr << "Cause: " << SDL_GetError() << std::endl;
        return -1;
    } catch (std::exception e) {
        std::cerr << e.what() << std::endl;
        return -1;
    }
    return 0;
}