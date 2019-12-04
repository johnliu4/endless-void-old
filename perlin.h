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
	PerlinNoise();
	~PerlinNoise();
	// removes the Perlin gradients
	void clear();
	// initializes a new matrix of gradients of size width * height
	void generate(const int width, const int height);
	GLfloat cosine_interp(GLfloat n1, GLfloat n2, GLfloat mu);
	GLfloat get_value(GLfloat x, GLfloat y);
};

#endif PERLIN_H