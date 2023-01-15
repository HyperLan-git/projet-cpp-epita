#include "entity/Sheep.hpp"

Sheep::Sheep(std::weak_ptr<World> world, SDL_Rect hitbox, SDL_Texture* texture,
             SDL_Point position, bool male)
    : Animal(world, hitbox, texture, position, male) {
    framecount = 10;
    life = 1500;
}

void Sheep::update() {
    if (luvTimer > 0) luvTimer--;
    if ((++framecount %= 100) == 0) {
        if (this->world.expired()) return;
        std::shared_ptr<World> w(this->world);
        if (!loved.expired()) {
            std::shared_ptr<Entity> lov(loved);
            chase(lov, 50);
            if (collidesWith(lov)) {
                SPAWN_ENTITY(Sheep, w, SDL_Rect(this->hitbox), this->texture,
                             SDL_Point(this->position), std::rand() % 2);
                lov.reset();
            }
        } else if (isMale() && (++luvTimer % 4) == 0 &&
                   (std::rand() % 4 == 0)) {
            constexpr Entity_pred predF = [](std::shared_ptr<Entity>& ptr) {
                return ptr->isSheep() && !ptr->isMale();
            };
            auto v = w->getEntitiesIf(predF);
            std::shared_ptr<Entity> e = getClosest(v);
            this->loved = std::weak_ptr<Entity>(e);
        }
        wander(50);

        constexpr Entity_pred predFriendly = [](std::shared_ptr<Entity>& ptr) {
            return ptr->isPrey() || ptr->isSheperd();
        };
        auto& e = getClosest(w->getEntitiesIf(predFriendly));
        if (e && collidesWith(e)) flee(e, 50);
    }
    Animal::update();
}

bool Sheep::isPrey() const { return true; }
bool Sheep::isSheep() const { return true; }