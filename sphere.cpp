#include "sphere.h"

Sphere::Sphere(glm::vec3 pos, GLfloat radius)
	: pos(pos), radius(radius) {}

Sphere::Sphere(GLfloat radius)
	: Sphere(glm::vec3(0.0f), radius) {}