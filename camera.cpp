#include <glew/glew.h>
#include <iostream>
#include <glfw/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include "camera.h"
#include "loader.h"
#include "input_manager.h"

Camera::Camera() {
	proj_mat = glm::perspective(
		glm::radians(45.0f), 16.0f / 9.0f, 0.1f, 100.0f);
	view_mat = glm::lookAt(
		glm::vec3(4, 3, 3),
		glm::vec3(0, 0, 0),
		glm::vec3(0, 1, 0));
	model_mat = glm::mat4(1.0f);

	pitch = 0.0f;
	yaw = 0.0f;
	speed = 0.01f;
	pos = glm::vec3(4.0f, 3.0f, 3.0f);

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
	shader_mat_id = glGetUniformLocation(program_id, "mvp");
}

Camera::~Camera() {}

void Camera::update() {
	// attempt to move
	glm::vec3 disp(0.0f);

	InputManager* input_manager = InputManager::get_instance();
	if (input_manager->get_key(GLFW_KEY_W) == GLFW_PRESS) {
		disp.z -= 1.0f;
	}

	if (input_manager->get_key(GLFW_KEY_A) == GLFW_PRESS) {
		disp.x -= 1.0f;
	}

	if (input_manager->get_key(GLFW_KEY_S) == GLFW_PRESS) {
		disp.z += 1.0f;
	}

	if (input_manager->get_key(GLFW_KEY_D) == GLFW_PRESS) {
		disp.x += 1.0f;
	}

	if (disp.x * disp.x + disp.z * disp.z > 0.0001f) {
		disp = glm::normalize(disp);
		std::cout << disp.x << ", " << disp.z << std::endl;
		pos += disp;

		view_mat = glm::lookAt(
			pos,
			glm::vec3(0, 0, 0),
			glm::vec3(0, 1, 0));
	}
}

void Camera::render() {

	glm::mat4 mvp = proj_mat * view_mat * model_mat;
	glUseProgram(program_id);
	glUniformMatrix4fv(shader_mat_id, 1, GL_FALSE, &mvp[0][0]);
}