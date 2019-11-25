#include <sstream>

#include "aabb.h"

AABB::AABB(glm::vec3 pos, GLfloat width, GLfloat height, GLfloat length)
	: pos(pos), vel(0.0f), width(width), height(height), length(length), grounded(false) {}

AABB::AABB(GLfloat width, GLfloat height, GLfloat length)
	: AABB(glm::vec3(0.0f), width, height, length) {}

AABB::AABB(const AABB& aabb) {
	pos = aabb.pos;
	vel = aabb.vel;
	width = aabb.width;
	height = aabb.height;
	length = aabb.length;
	grounded = aabb.grounded;
}

AABB& AABB::operator=(const AABB& aabb) {
	pos = aabb.pos;
	vel = aabb.vel;
	width = aabb.width;
	height = aabb.height;
	length = aabb.length;
	grounded = aabb.grounded;
	return *this;
}

std::string AABB::to_string() {
	std::stringstream ss;
	ss << "AABB {";
	ss << " pos.x: " << std::to_string(pos.x);
	ss << ", pos.y: " << std::to_string(pos.y);
	ss << ", pos.z: " << std::to_string(pos.z);
	ss << ", width: " << std::to_string(width);
	ss << ", height: " << std::to_string(height);
	ss << ", length: " << std::to_string(length);
	ss << " }";
	return ss.str();
}