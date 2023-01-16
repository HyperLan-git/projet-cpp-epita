#include "entity/Sheep.hpp"

Sheep::Sheep(std::weak_ptr<World> world, SDL_Rect hitbox, SDL_Texture* texture,
             SDL_Point position, bool male)
    : Animal(world, hitbox, texture, position, male) {
    framecount = 10;
    life = 1500;
    luvTimer = 1500;
}

void Sheep::update() {
    if (luvTimer > 0) luvTimer--;
    if ((++framecount %= 25) == 0) {
        if (this->world.expired()) return;
        std::shared_ptr<World> w(this->world);
        if (!loved.expired()) {
            std::shared_ptr<Entity> lov(loved);
            chase(lov, 12);
            if (collidesWith(lov)) {
                SPAWN_ENTITY(Sheep, w, SDL_Rect(this->hitbox), this->texture,
                             SDL_Point(this->position), std::rand() % 2);
                loved.reset();
                luvTimer = 1500;
            }
        } else if (isMale() && luvTimer == 0 && (std::rand() % 12 == 0)) {
            constexpr Entity_pred predF = [](std::shared_ptr<Entity>& ptr) {
                return ptr->isSheep() && !ptr->isMale();
            };
            auto v = w->getEntitiesIf(predF);
            std::shared_ptr<Entity> e = getClosest(v);
            this->loved = std::weak_ptr<Entity>(e);
            wander(12);
        } else
            wander(12);

        constexpr Entity_pred predFriendly = [](std::shared_ptr<Entity>& ptr) {
            return ptr->isPrey() || ptr->isShepherd();
        };
        auto& e = getClosest(w->getEntitiesIf(predFriendly));
        if (e && collidesWith(e)) flee(e, 12);
    }
    Animal::update();
}

bool Sheep::isPrey() const { return true; }
bool Sheep::isSheep() const { return true; }