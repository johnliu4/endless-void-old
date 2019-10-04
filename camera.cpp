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

Camera::Camera(glm::vec3 pos, glm::vec3 dir) : Camera() {
	this->pos = pos;
	glm::vec3 dir_norm = glm::normalize(dir);
	// get normal of projection of direction vector onto xz plane
	glm::vec3 xz_plane_vec = glm::normalize(glm::vec3(dir_norm.x, 0.0f, dir_norm.z));
	std::cout << xz_plane_vec.x << ", " << xz_plane_vec.z << std::endl;
	// since a dot b = |a||b|cos(c) where c is the angle between a and b
	pitch = glm::acos(glm::dot(xz_plane_vec, dir_norm));
	if (dir_norm.y < 0.0f) {
		pitch *= -1.0f;
	}

	yaw = glm::acos(glm::dot(xz_plane_vec, glm::vec3(1.0f, 0.0f, 0.0f)));
}

Camera::~Camera() {}

void Camera::use_program() {
	glm::vec3 dir(1.0f, 0.0f, 0.0f);
	dir = glm::rotateZ(dir, pitch);
	dir = glm::rotateY(dir, yaw);
	view_mat = glm::lookAt(
		pos,
		pos + dir,
		glm::vec3(0.0f, 1.0f, 0.0f));

	glm::mat4 mvp = proj_mat * view_mat * model_mat;

	glUseProgram(program_id);
	glUniformMatrix4fv(shader_model_id, 1, GL_FALSE, &model_mat[0][0]);
	glUniformMatrix4fv(shader_view_id, 1, GL_FALSE, &view_mat[0][0]);
	glUniformMatrix4fv(shader_proj_id, 1, GL_FALSE, &proj_mat[0][0]);
	//glUniform3fv(shader_light_pos_id, 1, &light_pos[0]);
	glUniform3f(shader_light_pos_id, 0.0f, 10.0f, 0.0f);
}

void Camera::set_yaw(GLfloat yaw) {
	this->yaw = yaw;
}

GLfloat Camera::get_yaw() {
	return yaw;
}

void Camera::set_pitch(GLfloat pitch) {
	this->pitch = pitch;
}

GLfloat Camera::get_pitch() {
	return pitch;
}

void Camera::set_pos(glm::vec3 pos) {
	this->pos = pos;
}

glm::vec3 Camera::get_pos() {
	return pos;
}