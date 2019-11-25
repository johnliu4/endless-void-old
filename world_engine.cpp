#include <iostream>
#include <time.h>

#include <glew/glew.h>
#include <glfw/glfw3.h>

#include "world_engine.h"
#include "state_ingame.h"

WorldEngine::WorldEngine(int window_width, int window_height) {
	this->window_width = window_width;
	this->window_height = window_height;

	glewExperimental = true;
	if (!glfwInit()) {
		return;
	}

	window = glfwCreateWindow(window_width, window_height, "World Engine", nullptr, nullptr);
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

	input_manager = new InputManager();
	input_manager->set_window(window);
	physics_engine = new PhysicsEngine();
	render_engine = new RenderEngine();
	current_state = new StateIngame(input_manager, physics_engine, render_engine);
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

	double before_time = glfwGetTime();
	double fps_timer = 0;
	int frame_count = 0;

	while (running) {
		double current_time = glfwGetTime();
		double delta_time = current_time - before_time;
		before_time = current_time;

		frame_count++;
		fps_timer += delta_time;
		if (fps_timer >= 1.0) {
			fps_timer -= 1.0;
			glfwSetWindowTitle(window, ("World Engine FPS: " + std::to_string(frame_count)).c_str());
			frame_count = 0;
		}


		input_manager->poll_input();

		current_state->update();
		current_state->render();

		glfwSwapBuffers(window);
		if (glfwWindowShouldClose(window) || input_manager->get_key(GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			running = false;
		}
	}
}