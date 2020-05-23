#ifndef GAMES_ENGINEERING_CMP_CLEANUP_H
#define GAMES_ENGINEERING_CMP_CLEANUP_H

#include <ecm.h>

class CleanUpComponent : public Component
{
private:
	float _lifeTime;

public:
	CleanUpComponent() = delete;
	explicit CleanUpComponent(Entity* p, float lifeTime);

	void update(double dt) override;

	void render() override { }
};

#endif //GAMES_ENGINEERING_CMP_CLEANUP_H
