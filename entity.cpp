#include "entity.h"

unsigned int Entity::ID_COUNTER = 0;

Entity::Entity() : id(ID_COUNTER) {
	ID_COUNTER++;
}

unsigned int Entity::get_id() {
	return id;
}

void Entity::render() {};