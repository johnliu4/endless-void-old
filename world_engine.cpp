#include <iostream>

#include <glew/glew.h>
#include <glfw/glfw3.h>

#include "perlin.h"

int main() {
	PerlinNoise perlin(10, 5);
	for (int y = 0; y < 12; y++) {
		for (int x = 0; x < 27; x++) {
			std::cout << (int) (perlin.get_value(x / 3.0f, y / 3.0f) * 1.0f) << " ";
		}

		std::cout << std::endl;
	}
	/*
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


	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);


	// An array of 3 vectors which represents 3 vertices
	static const GLfloat g_vertex_buffer_data[] = {
	   -1.0f, -1.0f, 0.0f,
	   1.0f, -1.0f, 0.0f,
	   0.0f,  1.0f, 0.0f,
	};

	// This will identify our vertex buffer
	GLuint vertexbuffer;
	// Generate 1 buffer, put the resulting identifier in vertexbuffer
	glGenBuffers(1, &vertexbuffer);
	// The following commands will talk about our 'vertexbuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	// Give our vertices to OpenGL.
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	bool running = true;
	while (running) {

		// 1st attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);
		// Draw the triangle !
		glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
		glDisableVertexAttribArray(0);

		glfwSwapBuffers(window);
		glfwPollEvents();
		if (glfwWindowShouldClose(window)) {
			running = false;
		}
	}

	glfwTerminate();
	window = nullptr;
	return 0;*/
}