#ifndef RENDER_LOADER_H
#define RENDER_LOADER_H

#include <glew/glew.h>

GLuint load_shader(const char* file_path, const GLuint shader_type);

GLuint load_png(const char* file_path);

#endif