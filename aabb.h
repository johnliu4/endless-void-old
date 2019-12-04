#ifndef AABB_H
#define AABB_H

#include <string>

#include <glew/glew.h>
#include <glm/glm.hpp>

class AABB {
public:
	AABB(glm::vec3 pos, GLfloat width, GLfloat height, GLfloat length);
	AABB(GLfloat width, GLfloat height, GLfloat length);
	AABB(const AABB& aabb);
	AABB& operator=(const AABB& aabb);

	// position of center of box
	glm::vec3 pos;
	glm::vec3 vel;
	GLfloat width;
	GLfloat height;
	GLfloat length;
	bool grounded;

	std::string to_string();
};

#endif