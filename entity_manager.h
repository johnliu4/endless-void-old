#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include <list>

#include "render_engine.h"
#include "physics_engine.h"
#include "entity.h"

class EntityManager {
private:
	PhysicsEngine* physics_engine;
	RenderEngine* render_engine;
	std::list<Entity*> entity_list;

public:
	EntityManager(PhysicsEngine* physics_engine, RenderEngine* render_engine);
	~EntityManager();

	unsigned int add_entity(Entity* entity);
	void remove_entity(Entity* entity);
	void remove_entity(unsigned int id);

	std::list<Entity*>::iterator it_begin();
	std::list<Entity*>::iterator it_end();
};

#endif