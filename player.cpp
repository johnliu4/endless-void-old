#include <iostream>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include "player.h"

using glm::vec3;

GLfloat wire_frame_data[] = {
	-0.25f, -0.85f, 0.25f,
	0.25f, -0.85f, 0.25f,
	0.25f, -0.85f, 0.25f,
	0.25f, -0.85f, -0.25f,
	-0.25f, -0.85f, -0.25f,
	0.25f, -0.85f, -0.25f,
	-0.25f, -0.85f, 0.25f,
	-0.25f, -0.85f, -0.25f,

	-0.25f, 0.85f, 0.25f,
	0.25f, 0.85f, 0.25f,
	0.25f, 0.85f, 0.25f,
	0.25f, 0.85f, -0.25f,
	-0.25f, 0.85f, -0.25f,
	0.25f, 0.85f, -0.25f,
	-0.25f, 0.85f, 0.25f,
	-0.25f, 0.85f, -0.25f,


	-0.25f, -0.85f, 0.25f,
	-0.25f, 0.85f, 0.25f,

	0.25f, -0.85f, 0.25f,
	0.25f, 0.85f, 0.25f,

	0.25f, -0.85f, -0.25f,
	0.25f, 0.85f, -0.25f,

	-0.25f, -0.85f, -0.25f,
	-0.25f, 0.85f, -0.25f,
};

Player::Player(InputManager* input_manager, PhysicsEngine* physics_engine,
	Scene* scene, vec3 pos, vec3 eye_dir) : bounding_box(0.5f, 1.7f, 0.5f) {
	this->input_manager = input_manager;
	this->physics_engine = physics_engine;
	this->scene = scene;
	this->eye_dir = eye_dir;

	scene->set_camera_pos(pos);
	scene->set_camera_dir(eye_dir);

	bounding_box.pos = pos;


	max_sprint_speed = 2.0f;
	sprint_accel = 30.0f * physics_engine->TICK_TIME;
	max_run_speed = 3.0f;
	run_accel = 22.0f * physics_engine->TICK_TIME;
	max_crouch_speed = 0.3f;
	crouch_accel = 9.0f * physics_engine->TICK_TIME;
	in_air_accel = 1.0f * physics_engine->TICK_TIME;
	jump_strength = 5.3f;

	bounding_box.mass = 80.0f;
	bounding_box.base_friction = 1.1f;
	physics_engine->set_dynamic_aabb(&bounding_box);

	GLuint vertex_buffer_id;
	glGenBuffers(1, &vertex_buffer_id);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_id);
	glBufferData(GL_ARRAY_BUFFER, sizeof(wire_frame_data), wire_frame_data, GL_STATIC_DRAW);

	wireframe = new Wireframe(vertex_buffer_id, sizeof(wire_frame_data) / sizeof(GLfloat));
	scene->add_entity(wireframe);
}

Player::~Player() {
	delete wireframe;
}

void Player::update() {

	// handle mouse input
	glm::vec2 cursor_delta = input_manager->get_cursor_delta();
	input_manager->center_cursor();

	constexpr GLfloat pi = glm::pi<GLfloat>();

	GLfloat yaw = camera.get_yaw() - cursor_delta.x * 0.0007f;
	// keep yaw within range [0, 2*pi)
	yaw = fmod(yaw, pi * 2.0f);
	if (yaw < 0.0f) {
		yaw += pi * 2.0f;
	}

	GLfloat pitch = camera.get_pitch() - cursor_delta.y * 0.0007f;
	// clamp pitch between range [-pi/2, pi/2]
	if (pitch < -(pi * 0.5f)) {
		pitch = -(pi * 0.5f);
	} else if (pitch > pi * 0.5f) {
		pitch = pi * 0.5f;
	}

	camera.set_yaw(yaw);
	camera.set_pitch(pitch);

	// get the direction of the player from pitch and yaw
	vec3 dir(1.0f, 0.0f, 0.0f);
	dir = glm::rotateZ(dir, pitch);
	dir = glm::rotateY(dir, yaw);
	dir = glm::normalize(dir);

	// handle keyboard input
	vec3 disp(0.0f);
	bool axial_movement = false;
	if (input_manager->get_key(GLFW_KEY_W) == GLFW_PRESS) {
		disp.x += glm::cos(yaw);
		disp.z += glm::sin(-yaw);
		axial_movement = true;
	}

	if (input_manager->get_key(GLFW_KEY_S) == GLFW_PRESS) {
		disp.x += glm::cos(yaw + pi);
		disp.z += glm::sin(-(yaw + pi));
		if (axial_movement == true) {
			// if both and W and S keys are down they should cancel out
			axial_movement = false;
		} else {
			axial_movement = true;
		}
	}

	bool lateral_movement = false;
	if (input_manager->get_key(GLFW_KEY_A) == GLFW_PRESS) {
		disp.x += glm::cos(yaw + pi * 0.5f);
		disp.z += glm::sin(-(yaw + pi * 0.5f));
		lateral_movement = true;
	}

	if (input_manager->get_key(GLFW_KEY_D) == GLFW_PRESS) {
		disp.x += glm::cos(yaw - pi * 0.5f);
		disp.z += glm::sin(-(yaw - pi * 0.5f));
		if (lateral_movement) {
			// if both and A and D keys are down they should cancel out
			lateral_movement = false;
		} else {
			lateral_movement = true;
		}
	}

	bool jumping = false;
	if (bounding_box.grounded) {
		if (input_manager->get_key(GLFW_KEY_SPACE) == GLFW_PRESS) {
			jumping = true;
		}
	}

	/*
	// flying movement
	if (input_manager->get_key(GLFW_KEY_W) == GLFW_PRESS) {
		disp.x += glm::cos(pitch) * glm::cos(yaw);
		disp.y += glm::sin(pitch);
		disp.z += glm::cos(pitch) * glm::sin(-yaw);
	}

	if (input_manager->get_key(GLFW_KEY_A) == GLFW_PRESS) {
		disp.x = glm::cos(yaw + pi * 0.5f);
		disp.z = glm::sin(-(yaw + pi * 0.5f));
	}

	if (input_manager->get_key(GLFW_KEY_S) == GLFW_PRESS) {
		disp.x += glm::cos(pitch) * glm::cos(yaw + pi);
		disp.y -= glm::sin(pitch);
		disp.z += glm::cos(pitch) * glm::sin(-(yaw + pi));
	}

	if (input_manager->get_key(GLFW_KEY_D) == GLFW_PRESS) {
		disp.x += glm::cos(yaw - pi * 0.5f);
		disp.z += glm::sin(-(yaw - pi * 0.5f));
	}

	if (input_manager->get_key(GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
		disp.y += 1.0f;
	}

	if (input_manager->get_key(GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
		disp.y -= 1.0f;
	}*/

	// determine if player is trying to move
	if (axial_movement || lateral_movement) {
		vec3 vel = glm::normalize(disp);
		// check if the player is grounded (not in air)
		if (bounding_box.grounded) {
			vel *= run_accel;
			GLfloat current_vel_length = glm::length(bounding_box.vel);
			GLfloat after_vel_length = glm::length(bounding_box.vel + vel);

			// if the player doesn't exceed the max running speed in this frame
			// then simply add the change in velocity to the player
			if (after_vel_length <= max_run_speed) {
				bounding_box.vel += vel;
			} else {
				// if the player will exceed the max running speed in this very frame,
				// cap their speed to the run speed
				if (current_vel_length <= max_run_speed) {
					bounding_box.vel += vel;
					bounding_box.vel = glm::normalize(bounding_box.vel) * max_run_speed;
				} else {
					// if the player already exceeds the max running speed, then do not
					// increase/decrease speed, and only change direction
					// friction from the surface will naturally slow the player down
					bounding_box.vel += vel;
					bounding_box.vel = glm::normalize(bounding_box.vel) * current_vel_length;
				}
			}
		} else {
			// freely add to player velocity in air
			// there is nothing (except air) to slow down player
			vel *= in_air_accel;
			bounding_box.vel.x += vel.x;
			bounding_box.vel.z += vel.z;
		}
	}

	if (jumping) {
		bounding_box.vel.y += jump_strength;
	}

	scene->set_camera_pos(bounding_box.pos + glm::vec3(0.0f, 0.75f, 0.0f));
	scene->set_camera_dir(dir);
	wireframe->set_pos(bounding_box.pos);
}

void Player::render() {
	camera.use_program();
}

vec3 Player::get_pos() {
	return bounding_box.pos;
}

void Player::set_pos(vec3 pos) {
	bounding_box.pos = pos;
}

vec3 Player::get_vel() {
	return bounding_box.vel;
}

void Player::set_vel(vec3 vel) {
	bounding_box.vel = vel;
}