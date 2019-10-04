#ifndef AABB_H
#define AABB_H

#include <glew/glew.h>
#include <glm/glm.hpp>

class AABB {
public:
	// position of center of box
	glm::vec3 pos;
	GLfloat width;
	GLfloat height;
	GLfloat length;
	AABB(glm::vec3 pos, GLfloat width, GLfloat height, GLfloat length);
	AABB(GLfloat width, GLfloat height, GLfloat length);
};

#endif