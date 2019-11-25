#ifndef BUSH1_H
#define BUSH1_H

#include <glm/glm.hpp>

#include "entity.h"
#include "scene_entity.h"
#include "aabb.h"

class Bush1 : public Entity {
private:
	static GLuint vertex_buffer_id;
	static GLuint uv_buffer_id;
	static GLuint texture_id;
	static GLuint num_vertices;
	static bool scene_entity_init;

	SceneEntity* scene_entity;

	AABB bounding_box;

public:
	Bush1(glm::vec3 pos, GLfloat size);
	~Bush1();
	void update();
	void render();

	SceneEntity& get_scene_entity();
	AABB& get_bounding_box();
};

#endif