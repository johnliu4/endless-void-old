#include "bush1.h"
#include "obj_loader.h"
#include "render_loader.h"

GLuint Bush1::vertex_buffer_id = 0;
GLuint Bush1::uv_buffer_id = 0;
GLuint Bush1::texture_id = 0;
GLuint Bush1::num_vertices = 0;
bool Bush1::scene_entity_init = false;

Bush1::Bush1(glm::vec3 pos, GLfloat size) : bounding_box(pos, size, size, size) {
	scene_entity = load_obj("./resources/bush1.obj");
	scene_entity->set_pos(pos);
	scene_entity->set_scale(glm::vec3(size, size, size));
}

Bush1::~Bush1() {
	delete scene_entity;
}

void Bush1::update() {}
void Bush1::render() {}

SceneEntity& Bush1::get_scene_entity() {
	return *scene_entity;
}

AABB& Bush1::get_bounding_box() {
	return bounding_box;
}