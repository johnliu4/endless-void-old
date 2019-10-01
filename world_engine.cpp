#include <iostream>
#include <time.h>

#include <glew/glew.h>
#include <glfw/glfw3.h>

#include "world_engine.h"
#include "state_ingame.h"
#include "perlin.h"
#include "terrain.h"

WorldEngine::WorldEngine(int window_width, int window_height) {
	this->window_width = window_width;
	this->window_height = window_height;

	glewExperimental = true;
	if (!glfwInit()) {
		return;
	}

	window = glfwCreateWindow(window_width, window_height, "Hello world!", nullptr, nullptr);
	if (!window) {
		std::cout << "Failed to create GLFW window." << std::endl;
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(window);

	GLenum err = glewInit();
	if (err != GLEW_OK) {
		std::cout << "Failed to init GLEW." << std::endl;
		return;
	}

	if (glfwRawMouseMotionSupported()) {
		glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
	}

	srand(time(nullptr));

	input_manager = InputManager::get_instance();
	input_manager->set_window(window);
	physics_engine = new PhysicsEngine();
	render_engine = new RenderEngine();
	current_state = new StateIngame();
}

WorldEngine::~WorldEngine() {
	delete input_manager;
	delete physics_engine;
	delete render_engine;
	delete current_state;
	glfwTerminate();
}

void WorldEngine::start() {
	game_loop();
}

void WorldEngine::game_loop() {
	bool running = true;
	while (running) {
		input_manager->poll_input();
		current_state->update();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		current_state->render();

		glfwSwapBuffers(window);
		if (glfwWindowShouldClose(window) || input_manager->get_key(GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			running = false;
		}
	}
}