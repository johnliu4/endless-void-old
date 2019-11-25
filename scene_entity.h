#ifndef SCENE_ENTITY_H
#define SCENE_ENTITY_H

#include <vector>

#include <glew/glew.h>
#include <glm/glm.hpp>

/* A renderable entity. */

struct SceneEntityTexture {
	GLuint texture_id;
	GLuint start_index;
	GLuint num_vertices;
};

class SceneEntity {
protected:
	GLuint vertex_buffer_id;
	GLuint uv_buffer_id;
	GLuint texture_id;

	bool using_textures;
	unsigned int num_vertices;
	glm::vec3 pos;
	glm::vec3 scale;
	glm::vec3 rot_axis;
	// in degrees
	GLfloat rot_angle;

	std::vector<SceneEntityTexture> texture_list;

	SceneEntity();
public:
	SceneEntity(GLuint vertex_buffer_id, unsigned int num_vertices);
	SceneEntity(GLuint vertex_buffer_id, GLuint uv_buffer_id, GLuint texture_id, unsigned int num_vertices);
	SceneEntity(GLuint vertex_buffer_id, GLuint uv_buffer_id, std::vector<SceneEntityTexture> texture_list);
	~SceneEntity();

	virtual void render(GLuint model_matrix_id);

	void set_pos(glm::vec3 pos);
	void set_scale(glm::vec3 scale);
	void set_rotation_axis(glm::vec3 axis);
	void set_rotation_angle(GLfloat angle);
};

#endif