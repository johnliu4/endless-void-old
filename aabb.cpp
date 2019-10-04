#include "aabb.h"

AABB::AABB(glm::vec3 pos, GLfloat width, GLfloat height, GLfloat length)
	: pos(pos), width(width), height(height), length(length) {}

AABB::AABB(GLfloat width, GLfloat height, GLfloat length)
	: AABB(glm::vec3(0.0f), width, height, length) {}