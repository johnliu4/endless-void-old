#ifndef WORLD_H
#define WORLD_H

#include <glew/glew.h>

#include "input_manager.h"
#include "physics_engine.h"
#include "render_engine.h"
#include "entity_manager.h"

#include "scene.h"
#include "player.h"
#include "crate.h"
#include "terrain.h"
#include "maze.h"
#include "path_generator.h"
#include "bush1.h"
#include "slate_platform1.h"

class World {
private:
	InputManager* input_manager;
	PhysicsEngine* physics_engine;
	RenderEngine* render_engine;
	EntityManager* entity_manager;

	PathGenerator* path_generator;

	Scene* world_scene;
	Crate* crate;

	Player* player;

public:
	World(InputManager* input_manager, PhysicsEngine* physics_engine, RenderEngine* render_engine);
	~World();
	void update();
	void render();
};

#endif