#ifndef PATH_GENERATOR_H
#define PATH_GENERATOR_H

#include <list>

#include "physics_engine.h"
#include "scene.h"
#include "floor.h"
#include "floor_normal.h"
#include "player.h"

/* Generator for a randomized game world. */

class PathGenerator {
	std::list<Floor*> floors;
	Player* player;
	PhysicsEngine* physics_engine;
	Scene* scene;
	// maximal distance player has travelled along path
	GLfloat max_player_distance;
	// minimum length of pathing to keep in front of player
	GLfloat min_forward_length;
	// maximum length of pathing to keep behind player
	GLfloat max_backward_length;
	// current distance to the front of the path
	GLfloat current_forward_distance;
	// current distance to the back of the path
	GLfloat current_backward_distance;
	GLfloat score;

	// generates one new floor
	void generate_new_floor();

public:
	PathGenerator(Player* player, PhysicsEngine* physics_engine, Scene* scene);
	~PathGenerator();
	void update();
};

#endif PATH_GENERATOR_H