#include <glew/glew.h>
#include <iostream>
#include <glfw/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include "camera.h"
#include "loader.h"
#include "input_manager.h"

Camera::Camera() {
	proj_mat = glm::perspective(
		glm::radians(45.0f), 16.0f / 9.0f, 0.1f, 200.0f);
	view_mat = glm::mat4(1.0f);
	model_mat = glm::mat4(1.0f);

	pitch = 0.0f;
	yaw = 0.0f;
	speed = 0.01f;
	pos = glm::vec3(0.0f, 0.0f, 1.0f);

	program_id = glCreateProgram();
	GLuint vertex_id = load_shader("camera_vert.glsl", GL_VERTEX_SHADER);
	GLuint fragment_id = load_shader("camera_frag.glsl", GL_FRAGMENT_SHADER);
	glAttachShader(program_id, vertex_id);
	glAttachShader(program_id, fragment_id);
	glLinkProgram(program_id);
	glDetachShader(program_id, vertex_id);
	glDetachShader(program_id, fragment_id);
	glDeleteShader(vertex_id);
	glDeleteShader(fragment_id);



	shader_model_id = glGetUniformLocation(program_id, "model");
	shader_view_id = glGetUniformLocation(program_id, "view");
	shader_proj_id = glGetUniformLocation(program_id, "proj");
	shader_light_pos_id = glGetUniformLocation(program_id, "light_worldspace_pos");
}

Camera::~Camera() {}

void Camera::update() {
	// attempt to move
	glm::vec3 disp(0.0f);

	InputManager* input_manager = InputManager::get_instance();
	glm::vec2 cursor_delta = input_manager->get_cursor_delta();
	input_manager->center_cursor();

	constexpr GLfloat pi = glm::pi<GLfloat>();
	yaw -= cursor_delta.x * 0.0007f;
	yaw = fmod(yaw, pi * 2.0f);
	if (yaw < 0.0f) {
		yaw += pi * 2.0f;
	}

	pitch -= cursor_delta.y * 0.0007f;
	if (pitch < -(pi * 0.5f)) {
		pitch = -(pi * 0.5f);
	} else if (pitch > pi * 0.5f) {
		pitch = pi * 0.5f;
	}

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

	if (input_manager->get_key(GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
		disp.y += 1.0f;
	}

	if (input_manager->get_key(GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
		disp.y -= 1.0f;
	}


	glm::vec3 dir(1.0f, 0.0f, 0.0f);
	dir = glm::rotateZ(dir, pitch);
	dir = glm::rotateY(dir, yaw);


	if (disp.x * disp.x + disp.y * disp.y + disp.z * disp.z > 0.0001f) {
		disp = glm::normalize(disp);
		pos += disp * 0.2f;
	}

	view_mat = glm::lookAt(
		pos,
		pos + dir,
		glm::vec3(0.0f, 1.0f, 0.0f));
}

void Camera::render() {
	glm::mat4 mvp = proj_mat * view_mat * model_mat;
	glm::vec3 light_pos(0.0f, 5.0f, 0.0f);
	glUseProgram(program_id);
	glUniformMatrix4fv(shader_model_id, 1, GL_FALSE, &model_mat[0][0]);
	glUniformMatrix4fv(shader_view_id, 1, GL_FALSE, &view_mat[0][0]);
	glUniformMatrix4fv(shader_proj_id, 1, GL_FALSE, &proj_mat[0][0]);
	//glUniform3fv(shader_light_pos_id, 1, &light_pos[0]);
	glUniform3f(shader_light_pos_id, 0.0f, 10.0f, 0.0f);
}