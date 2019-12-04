#ifndef PLANE_H
#define PLANE_H

#include <glew/glew.h>
#include <glm/glm.hpp>

class Plane {
public:
	glm::vec3 norm;
	// any point that resides on the plane
	glm::vec3 point;
	Plane(glm::vec3 norm, glm::vec3 point);
};

#endif