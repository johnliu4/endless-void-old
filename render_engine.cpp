#include "render_engine.h"

RenderEngine* RenderEngine::singleton = nullptr;

RenderEngine::RenderEngine() {
	glGenVertexArrays(1, &vertex_array_id);
	glBindVertexArray(vertex_array_id);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);

	texture_manager = new TextureManager();
	RenderEngine::singleton = this;
}

RenderEngine::~RenderEngine() {}

RenderEngine* RenderEngine::get_instance() {
	return RenderEngine::singleton;
}

TextureManager* RenderEngine::get_texture_manager() {
	return texture_manager;
}


void RenderEngine::render() {
	for (auto it = scene_list.begin(); it != scene_list.end(); it++) {
		(*it)->render();
	}
}

void RenderEngine::add_scene(Scene* scene) {
	scene_list.push_back(scene);
}

void RenderEngine::remove_scene(Scene* scene) {
	scene_list.remove(scene);
}