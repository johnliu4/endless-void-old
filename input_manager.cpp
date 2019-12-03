#include <iostream>

#include "input_manager.h"

InputManager* InputManager::instance = nullptr;

InputManager::InputManager() : prev_cursor_pos(0.0f) {
	window = nullptr;
}

InputManager* InputManager::get_instance() {
	if (InputManager::instance == nullptr) {
		InputManager::instance = new InputManager();
	}

	return InputManager::instance;
}

int InputManager::get_key(int glfw_key) {
	return glfwGetKey(window, glfw_key);
}

glm::dvec2 InputManager::get_cursor_pos() {
	glm::dvec2 pos;
	glfwGetCursorPos(window, &pos.x, &pos.y);
	return pos;
}

void InputManager::set_cursor_pos(double x, double y) {
	glfwSetCursorPos(window, x, y);
}

glm::vec2 InputManager::get_cursor_delta() {
	double x_pos, y_pos;
	glfwGetCursorPos(window, &x_pos, &y_pos);
	glm::vec2 pos((float) x_pos, (float) y_pos);
	glm::vec2 delta = pos - prev_cursor_pos;
	prev_cursor_pos = pos;
	return delta;
}

void InputManager::center_cursor() {
	int width, height;
	glfwGetWindowSize(window, &width, &height);
	glfwSetCursorPos(window, width / 2, height / 2);
	prev_cursor_pos.x = width / 2.0f;
	prev_cursor_pos.y = height / 2.0f;
}

void InputManager::poll_input() {
	glfwPollEvents();
}

void InputManager::set_window(GLFWwindow* window) {
	this->window = window;
	glfwSetMouseButtonCallback(window, mouse_button_callback);
}

void InputManager::add_mouse_button_event(MouseButtonEvent event) {
	mouse_button_events.push(event);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
	InputManager* input_manager = InputManager::get_instance();
	double x, y;
	glfwGetCursorPos(window, &x, &y);
	input_manager->add_mouse_button_event({ button, action, mods, x, y });
}

std::queue<MouseButtonEvent>& InputManager::get_mouse_button_events() {
	return mouse_button_events;
}