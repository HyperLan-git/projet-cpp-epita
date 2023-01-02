#include "entity/Sheep.hpp"

Sheep::Sheep(std::weak_ptr<World> world, SDL_Rect hitbox, SDL_Texture* texture,
             SDL_Point position, bool male)
    : Animal(world, hitbox, texture, position, male) {
    framecount = 10;
    life = 1500;
}

void Sheep::update() {
    if (this->world.expired()) return;
    std::shared_ptr<World> w(this->world);
    auto& e = getClosest(w->getEntities());
    if (e && collidesWith(e)) flee(e, 200);
    if ((++framecount %= 100) == 0)
        if (!loved.expired()) {
            std::shared_ptr<Entity> love(loved);
            chase(love, 50);
            if (collidesWith(love)) {
                std::shared_ptr<World> w(this->world);
                SPAWN_ENTITY(Sheep, w, SDL_Rect(this->hitbox), this->texture,
                             SDL_Point(this->position), std::rand() % 2);
                loved.reset();
            }
        } else {
            wander(50);
            if ((++luv % 5) == 2 && (std::rand() % 4 == 0)) {
                constexpr Entity_pred predF = [](std::shared_ptr<Entity>& ptr) {
                    return ptr->isSheep() && !ptr->isMale();
                };
                constexpr Entity_pred predM = [](std::shared_ptr<Entity>& ptr) {
                    return ptr->isSheep() && ptr->isMale();
                };
                auto v =
                    std::move(w->getEntitiesIf(this->isMale() ? predF : predM));
                std::shared_ptr<Entity> e = std::move(getClosest(v));
                this->loved = std::weak_ptr<Entity>(e);
            }
        }
    Animal::update();
}

bool Sheep::isPrey() const { return true; }
bool Sheep::isSheep() const { return true; }