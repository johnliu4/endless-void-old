#ifndef PERLIN_H
#define PERLIN_H

#include <glm/glm.hpp>
#include <glew/glew.h>

/* A Perlin noise generator */

class PerlinNoise {
private:
	// 2d array of gradient vectors
	int width, height;
	glm::vec2** grads;
public:
	PerlinNoise(const int width, const int height);
	~PerlinNoise();
	GLfloat get_value(GLfloat x, GLfloat y);
};

#endif PERLIN_H