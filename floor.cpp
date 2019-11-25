#include "floor.h"

Floor::Floor(glm::vec3 pos, glm::vec3 dir, GLfloat length) {
	this->pos = pos;
	this->dir = dir;
	this->length = length;

	scene_entity = nullptr;
}

Floor::~Floor() {}