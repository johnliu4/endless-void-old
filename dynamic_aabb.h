#ifndef DYNAMIC_AABB_H
#define DYNAMIC_AABB_H

#include <glm/glm.hpp>
#include "aabb.h"

class DynamicAABB : public AABB {
public:
	DynamicAABB(glm::vec3 pos, GLfloat width, GLfloat height, GLfloat length);
	DynamicAABB(GLfloat width, GLfloat height, GLfloat length);
	DynamicAABB& operator=(const AABB& aabb);
	
	GLfloat mass;
	// the base friction specifies generally much frictional
	// force this dynamic entity exhibits
	// values of 0.1 represent low friction (like steel on ice)
	// while values greater than 1.0 generally represents
	// high friction (like rubber on rubber)
	GLfloat base_friction;
};

#endif