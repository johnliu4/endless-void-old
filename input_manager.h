#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <glfw/glfw3.h>
#include <glm/glm.hpp>

class InputManager {
private:
	GLFWwindow* window;
	glm::vec2 prev_cursor_pos;

public:
	InputManager();
	int get_key(int glfw_key);
	glm::dvec2 get_cursor_pos();
	void set_cursor_pos(double x, double y);
	// gets the displacement of the cursor since the last time
	// this function was called
	glm::vec2 get_cursor_delta();
	void center_cursor();
	void poll_input();
	void set_window(GLFWwindow* window);
};

#endif