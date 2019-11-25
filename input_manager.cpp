#include "input_manager.h"

InputManager::InputManager() : prev_cursor_pos(0.0f) {
	window = nullptr;
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
}