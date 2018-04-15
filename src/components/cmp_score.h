#pragma once
#include "../../engine/lib_ecm/ecm.h"
#include "../GUI/panel.h"

class PlayerScoreComponent : public Component {
protected:
    Panel _panel;
    int _points;
    std::string TEXT;

public:
    PlayerScoreComponent() = delete;
    explicit PlayerScoreComponent(Entity* p);

    void update(double dt) override;
    void render() override;

    void increasePoints(int num);
    void decreasePoints(int num);
    int getPoints() const;
};