#include <iostream>
#include <string>

#include "game/Game.hpp"
#include "entity/Sheep.hpp"
#include "entity/Wolf.hpp"

// TODO inline what deserves to be

int main()
{
    try
    {
        Game g;
        g.getWorld()->spawn(std::move(std::make_unique<Sheep>(
            SDL_Rect({100, 100, 100, 100}), g.getRenderer()->getTexture("grass"),
            SDL_Point({100, 100}))));
        g.getWorld()->spawn(std::move(std::make_unique<Wolf>(
            SDL_Rect({200, 200, 100, 100}), g.getRenderer()->getTexture("grass"),
            SDL_Point({200, 200}))));
        g.run();
    }
    catch (const std::runtime_error &e)
    {
        std::cerr << e.what() << std::endl;
        std::cerr << "Cause: " << SDL_GetError() << std::endl;
        return -1;
    }
    catch (std::exception e)
    {
        std::cerr << e.what() << std::endl;
        return -1;
    }
    return 0;
}