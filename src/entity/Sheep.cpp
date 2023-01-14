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
        if (!isMale() && luvTimer == 0 && std::rand() % 3 == 0) {
            constexpr Entity_pred predM = [](std::shared_ptr<Entity>& ptr) {
                return ptr->isSheep() && ptr->isMale();
            };
            auto v = w->getEntitiesIf(predM);
            const std::shared_ptr<Entity>& e = getClosest(v);
            if (collidesWith(e)) {
                luvTimer = 600;
                SPAWN_ENTITY(Sheep, w, this->hitbox, this->texture,
                             this->position, std::rand() % 2);
            }
        }
        wander(50);

        constexpr Entity_pred predFriendly = [](std::shared_ptr<Entity>& ptr) {
            return ptr->isPrey() || ptr->isShepard();
        };
        auto& e = getClosest(w->getEntitiesIf(predFriendly));
        if (e && collidesWith(e)) flee(e, 50);
    }
    Animal::update();
}

bool Sheep::isPrey() const { return true; }
bool Sheep::isSheep() const { return true; }