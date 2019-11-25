#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "render_loader.h"
#include "lodepng.h"

GLuint load_shader(const char* file_path, const GLuint shader_type) {
	GLuint shader_id = glCreateShader(shader_type);

	// parse data from shader file
	std::string shader_data;
	std::ifstream shader_stream(file_path, std::ios::in);
	if (shader_stream.is_open()) {
		std::stringstream str_stream;
		str_stream << shader_stream.rdbuf();
		shader_data = str_stream.str();
		shader_stream.close();
	} else {
		std::cout << "Unable to load shader file: " << file_path << std::endl;
		std::cin.get();
		return 0;
	}

	// send shader data to OpenGL
	const char* src_ptr = shader_data.c_str();
	glShaderSource(shader_id, 1, &src_ptr, nullptr);
	glCompileShader(shader_id);

	// check for shader compilation errors
	GLint result;
	GLint log_len;
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &result);
	glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &log_len);
	if (log_len > 0) {
		GLchar* msg = new GLchar[log_len + 1];
		glGetShaderInfoLog(shader_id, log_len, nullptr, &msg[0]);
		std::cout << "Shader compilation error: " << msg;
		delete[] msg;
	}

	return shader_id;
}

GLuint load_png(const char* file_path) {
	std::vector<unsigned char> image;
	unsigned int width, height;
	unsigned int error = lodepng::decode(image, width, height, file_path);

	if (error != 0) {
		std::cout << "Load PNG error " << error << ": " << lodepng_error_text(error) << std::endl;
		return 0;
	}

	GLuint texture_id;
	glGenTextures(1, &texture_id);
	glBindTexture(GL_TEXTURE_2D, texture_id);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &image[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	return texture_id;
}