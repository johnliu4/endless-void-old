#include <glew/glew.h>

#include "render_engine.h"

RenderEngine* RenderEngine::instance = nullptr;
RenderEngine* RenderEngine::get_instance() {
	if (instance == nullptr) {
		instance = new RenderEngine();
	}

	return instance;
}

RenderEngine::RenderEngine() {
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);
}

RenderEngine::~RenderEngine() {
	delete instance;
}

// initializes the render engine
// this needs to be called only once
void RenderEngine::init() {

}