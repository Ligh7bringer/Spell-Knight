#pragma once
#include <engine.h>

class EntityFactory {
public:
    EntityFactory() = delete;

    static std::shared_ptr<Entity> makePlayer(Scene* scene, const sf::Vector2f& pos);
    static std::shared_ptr<Entity> makeSnake(Scene* scene, const sf::Vector2f& pos);
    static void makeWalls(Scene* scene);
};