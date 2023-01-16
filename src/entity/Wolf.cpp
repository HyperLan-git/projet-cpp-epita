#include "entity/Wolf.hpp"

Wolf::Wolf(std::weak_ptr<World> world, SDL_Rect hitbox, SDL_Texture* texture,
           SDL_Point position)
    : Animal(world, hitbox, texture, position, true) {
    framecount = 10;
    life = 2500;
}
void Wolf::update() {
    if (this->world.expired()) return;
    if (--life == 0) this->kill();
    if ((++framecount %= 25) == 0) {
        std::shared_ptr<World> w(this->world);
        constexpr Entity_pred predShepherd = [](std::shared_ptr<Entity>& ptr) {
            return ptr->isShepherd();
        };
        std::vector<std::shared_ptr<Entity>> vec =
            w->getEntitiesIf(predShepherd);
        std::shared_ptr<Entity> spook = getClosest(vec);

        if (spook && dist(this->getPosition(), spook->getPosition()) < 200) {
            // Scared by shepherd or shepherd dog
            flee(spook, 25);
        } else if (life < 2000) {
            // HUNGRY
            if (!prey.expired()) {
                std::shared_ptr<Entity> e(prey);
                if (collidesWith(e)) {
                    flee(e, 25);
                    e->kill();
                    life += 400;
                } else
                    chase(e, 25);
            } else {
                constexpr Entity_pred predPrey =
                    [](std::shared_ptr<Entity>& ptr) { return ptr->isPrey(); };
                std::shared_ptr<Entity> kil =
                    getClosest(w->getEntitiesIf(predPrey));
                if (kil) {
                    prey = std::weak_ptr<Entity>(kil);
                    chase(kil, 25);
                } else {
                    wander(25);
                }
            }
        } else {
            // Chillin
            wander(25);
        }
    }
    Animal::update();
}