#ifndef PLAYER_H
#define PLAYER_H

#include <glm/glm.hpp>

#include "camera.h"
#include "input_manager.h"

class Player {
private:
	InputManager* input_manager;
	Camera camera;
	glm::vec3 pos;
	glm::vec3 vel;
	glm::vec3 dir;

	GLfloat sprint_accel;
	GLfloat running_accel;
	GLfloat crouch_accel;

public:
	Player();
	Player(glm::vec3 pos, glm::vec3 dir);
	~Player();
	void update();
	void render();
};

#endif