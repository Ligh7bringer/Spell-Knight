#pragma once

#include "engine.h"
#include <SFML/Audio/Music.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

class Level2Scene : public Scene
{
public:
	void Load() override;

	void UnLoad() override;

	void Update(const double& dt) override;

	void Render() override;

	void Restart();
};
