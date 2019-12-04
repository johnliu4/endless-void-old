#ifndef FLOOR_NORMAL_H
#define FLOOR_NORMAL_H

#include "floor.h"
#include "physics_engine.h"
#include "scene.h"

class FloorNormal : public Floor {
private:
	PhysicsEngine* physics_engine;
	Scene* scene;

public:
	static const GLfloat length;

	FloorNormal(glm::vec3 pos, glm::vec3 dir, PhysicsEngine* physics_engine, Scene* scene);
	~FloorNormal();

	GLfloat get_length();
};

#endif