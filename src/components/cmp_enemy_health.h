#pragma once 
#include "../../engine/lib_ecm/ecm.h"
#include "../GUI/panel.h"

class EnemyHealthComponent : public Component {
protected:
    Panel _panel;
    int _health, _maxHealth;
    sf::Vector2f _offset;
    int _panelAlpha;
public:
    EnemyHealthComponent() = delete;
    explicit EnemyHealthComponent(Entity *p, int health);

    void update(double dt) override;
    void render() override;

    void increaseHealth(int num);
    void decreaseHealth(int num);
};