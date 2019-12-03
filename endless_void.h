#ifndef ENDLESS_VOID_H
#define ENDLESS_VOID_H

#include <glew/glew.h>
#include <glfw/glfw3.h>

#include "input_manager.h"
#include "physics_engine.h"
#include "render_engine.h"
#include "game_state.h"

class EndlessVoid {
private:
	// updates per second
	static const int TICK_RATE = 30;
	int window_width, window_height;

	GLFWwindow* window;
	InputManager* input_manager;
	PhysicsEngine* physics_engine;
	RenderEngine* render_engine;
	GameState* current_state;

	void game_loop();
public:
	EndlessVoid(int window_width, int window_height);
	~EndlessVoid();
	void start();
};

#endif