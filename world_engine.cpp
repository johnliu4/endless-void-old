#include <iostream>

#include <glew/glew.h>
#include <glfw/glfw3.h>

int main() {
	glewExperimental = true;
	if (!glfwInit()) {
		return -1;
	}

	GLFWwindow* window = glfwCreateWindow(1024, 768, "Hello world!", nullptr, nullptr);
	if (!window) {
		std::cout << "Failed to create GLFW window." << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	GLenum err = glewInit();
	if (err != GLEW_OK) {
		std::cout << "Failed to init GLEW." << std::endl;
		return -1;
	}

	bool running = true;
	while (running) {
		glfwSwapBuffers(window);
		glfwPollEvents();
		if (glfwWindowShouldClose(window)) {
			running = false;
		}
	}

	glfwTerminate();
	window = nullptr;
	return 0;
}