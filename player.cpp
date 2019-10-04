#include <glm/gtx/rotate_vector.hpp>
#include <iostream>

#include "player.h"

Player::Player() {
	input_manager = InputManager::get_instance();
	sprint_accel = 5.0f;
	running_accel = 3.0f;
	crouch_accel = 1.0f;
}

Player::Player(glm::vec3 pos, glm::vec3 dir) : Player() {
	this->pos = pos;
	this->dir = dir;
}

Player::~Player() {}

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
	glm::vec3 dir(1.0f, 0.0f, 0.0f);
	dir = glm::rotateZ(dir, pitch);
	dir = glm::rotateY(dir, yaw);
	dir = glm::normalize(dir);

	// handle keyboard input
	glm::vec3 disp(0.0f);
	if (input_manager->get_key(GLFW_KEY_W) == GLFW_PRESS) {
		disp.x = glm::cos(pitch) * glm::cos(yaw);
		disp.y = glm::sin(pitch);
		disp.z = glm::cos(pitch) * glm::sin(-yaw);
	}

	if (input_manager->get_key(GLFW_KEY_A) == GLFW_PRESS) {
		disp.x = glm::cos(yaw + pi * 0.5f);
		disp.z = glm::sin(-(yaw + pi * 0.5f));
	}

	if (input_manager->get_key(GLFW_KEY_S) == GLFW_PRESS) {
		disp.x = glm::cos(pitch) * glm::cos(yaw + pi);
		disp.y = -glm::sin(pitch);
		disp.z = glm::cos(pitch) * glm::sin(-(yaw + pi));
	}

	if (input_manager->get_key(GLFW_KEY_D) == GLFW_PRESS) {
		disp.x = glm::cos(yaw - pi * 0.5f);
		disp.z = glm::sin(-(yaw - pi * 0.5f));
	}

	constexpr GLfloat epsilon = glm::epsilon<float>();
	if (glm::length(disp) > epsilon) {
		disp = glm::normalize(disp);
		disp *= sprint_accel;
		pos += disp;
	}

	camera.set_pos(pos);
}

void Player::render() {
	camera.use_program();
}