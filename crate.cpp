#include "crate.h"
#include "obj_loader.h"
#include "render_loader.h"

GLuint Crate::vertex_buffer_id = 0;
GLuint Crate::uv_buffer_id = 0;
GLuint Crate::texture_id = 0;
GLuint Crate::num_vertices = 0;
bool Crate::scene_entity_init = false;

Crate::Crate(glm::vec3 pos, GLfloat size) : bounding_box(pos, size, size, size) {
	scene_entity = load_obj("./resources/crate1.obj");
	scene_entity->set_pos(pos);
	scene_entity->set_scale(glm::vec3(size, size, size));
}

Crate::~Crate() {
	delete scene_entity;
}

void Crate::update() {}
void Crate::render() {}

SceneEntity& Crate::get_scene_entity() {
	return *scene_entity;
}

AABB& Crate::get_bounding_box() {
	return bounding_box;
}