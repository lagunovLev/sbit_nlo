#pragma once
#include "airship.h"

class UFO : public Airship
{
	float reload;
public:
	UFO(sf::Vector2f pos, float speed, float scale = 1.0f);
	UFO() { };
	void update() override;
	void destroy() override;
};