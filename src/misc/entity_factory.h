#pragma once
#include "../../engine/src/engine.h"

class EntityFactory {
public:
    EntityFactory() = delete;

    static std::shared_ptr<Entity> makePlayer(Scene* scene, const sf::Vector2f& pos);
    static std::shared_ptr<Entity> makeSlime(Scene* scene, const sf::Vector2f& pos);
    static std::shared_ptr<Entity> makeEyeDemon(Scene* scene, const sf::Vector2f& pos);
    static void makeWalls(Scene* scene);
    static std::shared_ptr<Entity> makePowerUp(Scene* scene, const sf::Vector2f& pos);
    static std::shared_ptr<Entity> makeFish(Scene* scene, const sf::Vector2f& pos);
    static std::shared_ptr<Entity> makePlant(Scene* scene, const sf::Vector2f& pos);
    static std::shared_ptr<Entity> makeBird(Scene* scene, const sf::Vector2f& pos);
};