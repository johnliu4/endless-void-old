#include "entity_manager.h"

EntityManager::EntityManager(PhysicsEngine* physics_engine, RenderEngine* render_engine) {
	this->physics_engine = physics_engine;
	this->render_engine = render_engine;
}

EntityManager::~EntityManager() {
	while (entity_list.size() != 0) {
		Entity* entity = entity_list.back();
		delete entity;
		entity_list.pop_back();
	}
}

unsigned int EntityManager::add_entity(Entity* entity) {
	entity_list.push_back(entity);
	return entity->get_id();
}

void EntityManager::remove_entity(Entity* entity) {
	entity_list.remove(entity);
	delete entity;
}

void EntityManager::remove_entity(unsigned int id) {
	for (auto it = entity_list.begin(); it != entity_list.end(); it++) {
		if ((*it)->get_id() == id) {
			entity_list.erase(it);
			delete* it;
			break;
		}
	}
}

std::list<Entity*>::iterator EntityManager::it_begin() {
	return entity_list.begin();
}

std::list<Entity*>::iterator EntityManager::it_end() {
	return entity_list.end();
}