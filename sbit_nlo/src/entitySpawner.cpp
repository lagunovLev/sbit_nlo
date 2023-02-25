#include "entitySpawner.h"
#include "game.h"
#include "airship.h"
#include "ufo.h"

#define FIRST_LAYER_Y -275
#define LAYERS_DISTANCE_Y 80
#define LAYERS_COUNT 5
#define AIRSHIP_SPEED 50
#define AIRSHIP_SCALE 2
#define UFO_SPEED 75
#define UFO_SCALE 2

EntitySpawner::EntitySpawner(std::list<Entity*>* enityList, float spawn_speed) : enityList(enityList), spawn_speed(spawn_speed)
{ 
	for (int i = 0, j = FIRST_LAYER_Y; i < LAYERS_COUNT; i++, j -= LAYERS_DISTANCE_Y)
		layers.push_back(j);
	for (int i = 0; i < LAYERS_COUNT; i++)
		layer_timers.push_back(((float)rand() / (RAND_MAX)));
}

void EntitySpawner::spawn()
{
	timer += spawn_speed * Game::elapsedSeconds;
	spawn_speed += 0.002 * Game::elapsedSeconds;

	for (int i = 0; i < LAYERS_COUNT; i++)
	{
		float r = ((float)rand() / (RAND_MAX) * 0.5) + 0.5;
		layer_timers[i] += 0.6 * Game::elapsedSeconds * r;
		layer_timers[i] = std::min(layer_timers[i], 1.0f);
	}

	while (timer >= 1.0f)
	{
		timer -= 1.0f;

		int index;
		int popitka = 10;
		do {
			index = rand() % LAYERS_COUNT;
			popitka--;
		} while (layer_timers[index] < 1 && popitka > 0);
		if (popitka == 0)
			continue;

		if (rand() % 2)
			enityList->push_back(new Airship(sf::Vector2f(0, layers[index]), AIRSHIP_SPEED, AIRSHIP_SCALE));
		else enityList->push_back(new UFO(sf::Vector2f(0, layers[index] - 3), UFO_SPEED, UFO_SCALE));

		layer_timers[index] -= 1;
	}
}

