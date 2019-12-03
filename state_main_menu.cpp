#include <iostream>

#include "state_main_menu.h"

StateMainMenu::StateMainMenu(
	InputManager* input_manager,
	RenderEngine* render_engine,
	GLFWwindow* window
) {
	this->input_manager = input_manager;
	this->render_engine = render_engine;
	this->window = window;
}

StateMainMenu::~StateMainMenu() {}

void StateMainMenu::update() {
	int window_width, window_height;
	glfwGetWindowSize(window, &window_width, &window_height);

	// process mouse button events
	std::queue<MouseButtonEvent>& events = input_manager->get_mouse_button_events();
	while (events.size() > 0) {
		MouseButtonEvent e = events.front();
		if (e.button == GLFW_MOUSE_BUTTON_LEFT && e.action == GLFW_PRESS) {
			std::cout << "click" << std::endl;
		}

		events.pop();
	}

	std::cout << input_manager->get_mouse_button_events().size() << std::endl;
}

void StateMainMenu::render() {

}