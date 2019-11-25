#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include "scene_entity.h"

SceneEntity::SceneEntity() {
	pos = glm::vec3(0.0f);
	scale = glm::vec3(1.0f);
	rot_axis = glm::vec3(1.0f, 0.0f, 0.0f);
	rot_angle = 0.0f;
	using_textures = false;
}

SceneEntity::SceneEntity(GLuint vertex_buffer_id, unsigned int num_vertices) : SceneEntity() {
	this->vertex_buffer_id = vertex_buffer_id;
	this->uv_buffer_id = 0;
	this->texture_id = 0;
	this->num_vertices = num_vertices;
}

SceneEntity::SceneEntity(GLuint vertex_buffer_id, GLuint uv_buffer_id, GLuint texture_id, unsigned int num_vertices) : SceneEntity() {
	this->vertex_buffer_id = vertex_buffer_id;
	this->uv_buffer_id = uv_buffer_id;
	this->texture_id = texture_id;
	this->num_vertices = num_vertices;
	using_textures = true;

	SceneEntityTexture texture;
	texture.texture_id = texture_id;
	texture.start_index = 0;
	texture.num_vertices = num_vertices;
	texture_list.push_back(texture);
}

SceneEntity::SceneEntity(GLuint vertex_buffer_id, GLuint uv_buffer_id, std::vector<SceneEntityTexture> texture_list) : SceneEntity() {
	this->vertex_buffer_id = vertex_buffer_id;
	this->uv_buffer_id = uv_buffer_id;
	this->texture_list = texture_list;
	using_textures = true;
}

SceneEntity::~SceneEntity() {}

void SceneEntity::render(GLuint model_matrix_id) {
	glm::mat4 transform = glm::scale(glm::rotate(glm::translate(glm::mat4(1.0f), pos), rot_angle, rot_axis), scale);
	glUniformMatrix4fv(model_matrix_id, 1, GL_FALSE, &transform[0][0]);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_id);
	glVertexAttribPointer(
		0,
		3,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*) 0
	);

	if (using_textures) {
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, uv_buffer_id);
		glVertexAttribPointer(
			1,
			2,
			GL_FLOAT,
			GL_FALSE,
			0,
			(void*)0
		);
	}

	for (int i = 0; i < texture_list.size(); i++) {
		SceneEntityTexture& texture = texture_list[i];
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture.texture_id);
		glDrawArrays(GL_TRIANGLES, texture.start_index, texture.num_vertices);
	}

	if (using_textures) {
		glDisableVertexAttribArray(1);
	}

	glDisableVertexAttribArray(0);
}

void SceneEntity::set_pos(glm::vec3 pos) {
	this->pos = pos;
}

void SceneEntity::set_scale(glm::vec3 scale) {
	this->scale = scale;
}

void SceneEntity::set_rotation_axis(glm::vec3 axis) {
	rot_axis = axis;
}

void SceneEntity::set_rotation_angle(GLfloat angle) {
	rot_angle = angle;
}
