
#include <iostream>
#include "floor_normal.h"

#include "obj_loader.h"
#include "render_loader.h"

const GLfloat FloorNormal::length = 16.0f;

FloorNormal::FloorNormal(
	glm::vec3 pos, glm::vec3 dir,
	PhysicsEngine* physics_engine,
	Scene* scene
	) : Floor(pos, dir, FloorNormal::length) {

	scene_entity = load_obj("./resources/floor1.obj");

	this->physics_engine = physics_engine;
	this->scene = scene;

	// init render
	scene_entity->set_pos(pos);
	scene->add_entity(scene_entity);

	// init physics
	bounding_boxes.reserve(3);
	bounding_boxes.push_back(new AABB(pos - glm::vec3(0.0f, 0.05f, 0.0f), 16.0f, 0.1f, 16.0f));
	bounding_boxes.push_back(new AABB(pos + glm::vec3(0.0f, 1.0f, 8.25f), 16.0f, 2.0f, 0.5f));
	bounding_boxes.push_back(new AABB(pos + glm::vec3(0.0f, 1.0f, -8.25f), 16.0f, 2.0f, 0.5f));
	for (std::vector<AABB*>::iterator it = bounding_boxes.begin(); it != bounding_boxes.end(); it++) {
		physics_engine->add_static_aabb(*it);
	}
}

FloorNormal::~FloorNormal() {
	// clean up physics entities
	for (std::vector<AABB*>::iterator it = bounding_boxes.begin(); it != bounding_boxes.end(); it++) {
		physics_engine->remove_static_aabb(*it);
		delete* it;
	}

	bounding_boxes.clear();
	// clean up render
	scene->remove_entity(scene_entity);
	delete scene_entity;

	std::cout << "deleted!" << std::endl;
}

GLfloat FloorNormal::get_length() {
	return FloorNormal::length;
}

