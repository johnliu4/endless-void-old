#ifndef WORLD_ENGINE_H
#define WORLD_ENGINE_H

#include <glfw/glfw3.h>

#include "input_manager.h"
#include "physics_engine.h"
#include "render_engine.h"
#include "game_state.h"

class WorldEngine {
private:
	// updates per second
	static const int TICK_RATE = 60;
	int window_width, window_height;

	GLFWwindow* window;
	InputManager* input_manager;
	PhysicsEngine* physics_engine;
	RenderEngine* render_engine;
	GameState* current_state;

	void game_loop();
public:
	WorldEngine(int window_width, int window_height);
	~WorldEngine();
	void start();
};

#endif