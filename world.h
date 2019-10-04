#ifndef WORLD_H
#define WORLD_H

#include "player.h"
#include "terrain.h"

class World {
private:
	Player* player;
	Terrain* terrain;
public:
	World();
	~World();
	void update();
	void render();
};

#endif