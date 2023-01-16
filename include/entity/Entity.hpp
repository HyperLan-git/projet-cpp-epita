#pragma once

class Entity;

#include <SDL2/SDL.h>

#include <memory>
#include <vector>

class World;

class Entity {
   public:
    Entity(std::weak_ptr<World> world, SDL_Point position, bool male);

    virtual void draw(SDL_Renderer* renderer) = 0;
    virtual void update() = 0;

    virtual bool collidesWith(const std::shared_ptr<Entity>& other) const {
        return false;
    }

    inline SDL_Point getPosition() const { return position; }

    bool isDead() const;
    void kill();

    // Can be killed by evil and carnivorous creatures
    virtual bool isPrey() const { return false; }

    // Scares off predators
    virtual bool isShepherd() const { return false; }

    // Can breed with another sheep
    virtual bool isSheep() const { return false; }

    inline bool isMale() const { return male; }

    const std::shared_ptr<Entity> getClosest(
        const std::vector<std::shared_ptr<Entity>>& entities) const;

    virtual ~Entity();

    friend bool operator==(const Entity& e, const Entity& e2);
    friend bool operator!=(const Entity& e, const Entity& e2);

   protected:
    SDL_Point position;

    void wander(unsigned speed);
    void chase(const std::shared_ptr<Entity>& other, int speed);
    void flee(const std::shared_ptr<Entity>& other, int speed);
    void chase(const SDL_Point p, int speed);
    void flee(const SDL_Point p, int speed);

    std::weak_ptr<World> world;

   private:
    bool dead = false;
    bool male;
};

int dist(const SDL_Point& p1, const SDL_Point& p2);

#include "game/World.hpp"
