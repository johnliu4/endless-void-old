#ifndef PLAYER_H
#define PLAYER_H

#include <glm/glm.hpp>

#include "dynamic_aabb.h"
#include "camera.h"
#include "input_manager.h"
#include "physics_engine.h"
#include "scene.h"
#include "wireframe.h"

using glm::vec3;

class Player {
private:
	InputManager* input_manager;
	PhysicsEngine* physics_engine;
	Scene* scene;
	Camera camera;
	DynamicAABB bounding_box;

	vec3 eye_dir;

	GLfloat max_sprint_speed;
	GLfloat sprint_accel;
	GLfloat max_run_speed;
	GLfloat run_accel;
	GLfloat max_crouch_speed;
	GLfloat crouch_accel;
	GLfloat in_air_accel;
	GLfloat jump_strength;

	Wireframe* wireframe;
public:
	Player(InputManager* input_manager, PhysicsEngine* physics_engine,
		Scene* scene, vec3 pos, vec3 eye_dir);
	~Player();
	void update();
	void render();

	vec3 get_pos();
	void set_pos(vec3 pos);
	vec3 get_vel();
	void set_vel(vec3 pos);
};

#endif