#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <glfw/glfw3.h>

class InputManager {
private:
	static InputManager* singleton;
	GLFWwindow* window;
	InputManager();
public:
	static InputManager* get_instance();
	~InputManager();

	int get_key(int glfw_key);
	void poll_input();
	void set_window(GLFWwindow* window);
};

#endif