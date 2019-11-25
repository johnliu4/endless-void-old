#ifndef SCENE_H
#define SCENE_H

#include <list>

#include <glm/glm.hpp>

#include "scene_entity.h"

class Scene {
private:
	GLuint default_program_id;
	std::list<SceneEntity*> entity_list;

	glm::mat4 view_matrix;
	glm::mat4 proj_matrix;

	GLuint model_matrix_id;
	GLuint view_matrix_id;
	GLuint proj_matrix_id;
	GLuint texture_sampler_id;

	GLfloat camera_fov;
	GLfloat camera_aspect_ratio;
	glm::vec3 camera_pos;
	glm::vec3 camera_dir;

public:
	Scene();
	~Scene();
	void render();

	void add_entity(SceneEntity* entity);
	void remove_entity(SceneEntity* entity);

	void set_camera_pos(glm::vec3 pos);
	void set_camera_dir(glm::vec3 dir);
};

#endif