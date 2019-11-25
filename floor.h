#ifndef FLOOR_H
#define FLOOR_H

#include <vector>
#include <glm/glm.hpp>

#include "aabb.h"
#include "scene_entity.h"

class Floor {
protected:
	// position of the center of the floor
	glm::vec3 pos;
	// direction that the player should be moving across this floor
	glm::vec3 dir;
	// length of this floor
	// this determines where the next floor will spawn
	GLfloat length;

	// collidable entities
	std::vector<AABB*> bounding_boxes;

	// renderable
	SceneEntity* scene_entity;

public:
	Floor(glm::vec3 pos, glm::vec3 dir, GLfloat length);
	virtual ~Floor();

	virtual GLfloat get_length() = 0;
};

#endif