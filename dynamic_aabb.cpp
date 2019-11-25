#include "dynamic_aabb.h"

DynamicAABB::DynamicAABB(glm::vec3 pos, GLfloat width, GLfloat height, GLfloat length)
	: AABB(pos, width, height, length) {
	mass = 1.0;
	base_friction = 0.5;
}

DynamicAABB::DynamicAABB(GLfloat width, GLfloat height, GLfloat length)
	: AABB(width, height, length) {
	mass = 1.0;
	base_friction = 0.5;
}

DynamicAABB& DynamicAABB::operator=(const AABB& aabb) {
	pos = aabb.pos;
	vel = aabb.vel;
	width = aabb.width;
	height = aabb.height;
	length = aabb.length;
	grounded = aabb.grounded;
	return *this;
}