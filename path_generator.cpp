#include <iostream>
#include <glm/gtx/string_cast.hpp>

#include "path_generator.h"

PathGenerator::PathGenerator(
	Player* player,
	PhysicsEngine* physics_engine,
	Scene* scene
	) {
	this->player = player;
	this->physics_engine = physics_engine;
	this->scene = scene;
	max_player_distance = 0.0f;
	min_forward_length = 100.0f;
	max_backward_length = 40.0f;
	current_forward_distance = 0.0f;
	current_backward_distance = 0.0f;
	score = 0.0f;

	while (current_forward_distance < min_forward_length) {
		generate_new_floor();
	}

}

PathGenerator::~PathGenerator() {
	for (std::list<Floor*>::iterator it = floors.begin(); it != floors.end(); it++) {
		delete *it;
	}

	floors.clear();
}

void PathGenerator::generate_new_floor() {
	GLfloat floor_length = FloorNormal::length;

	floors.push_back(new FloorNormal(
		glm::vec3(current_forward_distance + floor_length / 2.0f, 0.0f, 0.0f),
		glm::vec3(1.0f, 0.0f, 0.0f),
		physics_engine,
		scene));

	current_forward_distance += floor_length;
}

void PathGenerator::update() {
	glm::vec3 pos = player->get_pos();
	//std::cout << floors.size() << std::endl;
	if (pos.x > max_player_distance) {
		max_player_distance = pos.x;
	}

	//std::cout << max_player_distance << std::endl;

	// spawn a new floor if the player moves forward enough
	if (max_player_distance >= current_forward_distance - min_forward_length) {
		generate_new_floor();
	}

	// remove the floor farthest back if the player moves forward enough
	if (max_player_distance >= current_backward_distance + max_backward_length) {
		Floor* back = floors.front();
		current_backward_distance += back->get_length();
		delete back;
		floors.pop_front();
	}
} 
