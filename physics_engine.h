#ifndef PHYSICS_ENGINE_H
#define PHYSICS_ENGINE_H

#include <list>

#include <glew/glew.h>

#include "aabb.h"
#include "dynamic_aabb.h"

class PhysicsEngine {
private:
	DynamicAABB* dynamic_aabb;
	std::list<AABB*> static_aabbs;
public:
	// updates per second
	const int TICK_RATE = 30;
	// time between updates
	const GLfloat TICK_TIME = 1.0f / GLfloat(TICK_RATE);

	GLfloat gravity;

	PhysicsEngine();
	
	/* Updates all physics according to the TICK_TIME. */
	void update();

	void set_dynamic_aabb(DynamicAABB* aabb);

	void add_static_aabb(AABB* aabb);
	void remove_static_aabb(AABB* aabb);

	//void set_terrain(Terrain* terrain);
	//void set_player(Player* player);

	// attempts to move player based on their velocity
	//void update_player();
};

#endif