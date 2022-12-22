#include "entity/Wolf.hpp"

Wolf::Wolf(std::weak_ptr<World> world, SDL_Rect hitbox, SDL_Texture* texture,
           SDL_Point position)
    : Animal(world, hitbox, texture, position, true) {
    framecount = 10;
    life = 5000;
}

void Wolf::update() {
    if (this->world.expired()) return;
    if (--life == 0) this->kill();
    // HUNGRY
    if ((++framecount %= 100) == 0)
        if (life < 4500) {
            if (!prey.expired()) {
                std::shared_ptr<Entity> e(prey);
                if (collidesWith(e)) {
                    flee(e, 100);
                    e->kill();
                    life += 500;
                } else
                    chase(e, 100);
            } else {
                std::shared_ptr<World> w(this->world);
                constexpr Entity_pred predPrey =
                    [](std::shared_ptr<Entity>& ptr) { return ptr->isPrey(); };
                std::shared_ptr<Entity> kil =
                    getClosest(w->getEntitiesIf(predPrey));
                if (!kil) {
                    wander(100);
                    return;
                }
                prey = std::weak_ptr<Entity>(kil);
                chase(kil, 100);
            }
        } else {
            wander(100);
        }
    Animal::update();
}