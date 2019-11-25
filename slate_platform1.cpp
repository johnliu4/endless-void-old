#include "slate_platform1.h"
#include "obj_loader.h"
#include "render_loader.h"

GLuint SlatePlatform1::vertex_buffer_id = 0;
GLuint SlatePlatform1::uv_buffer_id = 0;
GLuint SlatePlatform1::num_vertices = 0;
GLuint SlatePlatform1::texture_id = 0;
bool SlatePlatform1::scene_entity_init = false;

SlatePlatform1::SlatePlatform1(glm::vec3 pos, GLfloat size) {
	scene_entity = load_obj("./resources/slate_platform1.obj");
	scene_entity->set_pos(pos);
	scene_entity->set_scale(glm::vec3(size, size, size));
}

SlatePlatform1::~SlatePlatform1() {
	delete scene_entity;
}

void SlatePlatform1::update() {}
void SlatePlatform1::render() {}

SceneEntity& SlatePlatform1::get_scene_entity() {
	return *scene_entity;
}