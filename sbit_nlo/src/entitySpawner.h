#pragma once
#include <list>
#include "entity.h"

class EntitySpawner
{
	std::list<Entity*>* enityList;
	std::vector<float> layers;
	std::vector<float> layer_timers;
	float timer = 0.0f;
	float spawn_speed;
public:
	EntitySpawner(std::list<Entity*>* enityList, float spawn_speed);
	EntitySpawner() { }
	void spawn();
};

