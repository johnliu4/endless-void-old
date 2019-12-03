#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <glfw/glfw3.h>
#include <glm/glm.hpp>

#include <queue>

struct MouseButtonEvent {
	int button;
	int action;
	int mods;
	double x;
	double y;
};

class InputManager {
private:
	static InputManager* instance;
	InputManager();

	GLFWwindow* window;
	glm::vec2 prev_cursor_pos;

	std::queue<MouseButtonEvent> mouse_button_events;

public:
	static InputManager* get_instance();

	int get_key(int glfw_key);
	glm::dvec2 get_cursor_pos();
	void set_cursor_pos(double x, double y);
	// gets the displacement of the cursor since the last time
	// this function was called
	glm::vec2 get_cursor_delta();
	void center_cursor();
	void poll_input();
	void set_window(GLFWwindow* window);

	void add_mouse_button_event(MouseButtonEvent event);

	std::queue<MouseButtonEvent>& get_mouse_button_events();
};

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

#endif