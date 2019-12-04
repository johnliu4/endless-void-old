#ifndef SLATE_PLATFORM1
#define SLATE_PLATFORM1

#include <glm/glm.hpp>

#include "entity.h"
#include "scene_entity.h"

class SlatePlatform1 : public Entity {
private:
	static GLuint vertex_buffer_id;
	static GLuint uv_buffer_id;
	static GLuint texture_id;
	static GLuint num_vertices;
	static bool scene_entity_init;

	SceneEntity* scene_entity;
public:
	SlatePlatform1(glm::vec3 pos, GLfloat size);
	~SlatePlatform1();
	void update();
	void render();

	SceneEntity& get_scene_entity();
};

#endif