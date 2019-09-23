#ifndef RENDER_ENGINE_H
#define RENDER_ENGINE_H

class RenderEngine {
private:
	static RenderEngine* instance;
public:
	static RenderEngine* get_instance();
	RenderEngine();
	~RenderEngine();
	void init();
};

#endif