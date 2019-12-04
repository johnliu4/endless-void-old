#ifndef ENTITY_H
#define ENTITY_H

#include <glew/glew.h>

/* An interactable game entity. */

class Entity {
private:
	static unsigned int ID_COUNTER;
	// a unique id to represent an instance of an entity
	const unsigned int id;

public:
	Entity();
	virtual void update() = 0;
	virtual void render();
	unsigned int get_id();
};

#endif