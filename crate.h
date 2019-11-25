#ifndef CRATE_H
#define CRATE_H

#include <glm/glm.hpp>

#include "entity.h"
#include "scene_entity.h"
#include "aabb.h"

class Crate : public Entity {
private:
	static GLuint vertex_buffer_id;
	static GLuint uv_buffer_id;
	static GLuint texture_id;
	static GLuint num_vertices;
	static bool scene_entity_init;
	
	SceneEntity* scene_entity;

	AABB bounding_box;

public:
	Crate(glm::vec3 pos, GLfloat size);
	~Crate();
	void update();
	void render();

	SceneEntity& get_scene_entity();
	AABB& get_bounding_box();
};

#endif