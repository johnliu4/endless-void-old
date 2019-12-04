#ifndef SPHERE_H
#define SPHERE_H

#include <glew/glew.h>
#include <glm/glm.hpp>

class Sphere {
public:
	glm::vec3 pos;
	GLfloat radius;
	Sphere(glm::vec3 pos, GLfloat radius);
	Sphere(GLfloat radius);
};

#endif SPHERE_H