#ifndef RENDER_ENGINE_H
#define RENDER_ENGINE_H

#include <list>

#include "scene.h"
#include "texture_manager.h"

class RenderEngine {
private:
	static RenderEngine* singleton;
	GLuint vertex_array_id;
	std::list<Scene*> scene_list;
	TextureManager* texture_manager;

public:
	static RenderEngine* get_instance();
	RenderEngine();
	~RenderEngine();

	TextureManager* get_texture_manager();

	void render();

	void add_scene(Scene* scene);
	void remove_scene(Scene* scene);
};

#endif