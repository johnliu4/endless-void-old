#include "input_manager.h"

InputManager* InputManager::singleton = nullptr;

InputManager* InputManager::get_instance() {
	if (singleton == nullptr) {
		singleton = new InputManager();
	}

	return singleton;
}

InputManager::InputManager() {
	window = nullptr;
}

InputManager::~InputManager() {
	delete singleton;
}

int InputManager::get_key(int glfw_key) {
	return glfwGetKey(window, glfw_key);
}

void InputManager::poll_input() {
	glfwPollEvents();
}

void InputManager::set_window(GLFWwindow* window) {
	this->window = window;
}