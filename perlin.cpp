#include <glm/glm.hpp>
#include <glm/gtc/random.hpp>

#include "perlin.h"

using glm::vec2;
using glm::dot;
using glm::diskRand;

PerlinNoise::PerlinNoise(const int width, const int height) {
	srand(time(0));
	this->width = width;
	this->height = height;
	// initialize 2d array of vectors to a random 2d unit vector
	grads = new vec2*[width];
	for (int x = 0; x < width; x++) {
		grads[x] = new vec2[height];
	}
	
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			grads[x][y] = diskRand(1.0f);
		}
	}
}

PerlinNoise::~PerlinNoise() {
	for (int x = 0; x < width; x++) {
		delete[] grads[x];
	}

	delete[] grads;
}

GLfloat lerp(GLfloat a0, GLfloat a1, GLfloat w) {
	return (1.0f - w) * a0 + w * a1;
}

// gets a Perlin value at a coordinate 
GLfloat PerlinNoise::get_value(GLfloat x, GLfloat y) {
	// find the grid coordinates the Perlin coordinates belong to
	int grid_x = (int) x;
	int grid_y = (int) y;
	// ensure they are not out of bounds
	if (grid_x < 0 || grid_y < 0 || grid_x >= width - 1 || grid_y >= height - 1) {
		return 0.0f;
	}

	GLfloat n0 = dot(grads[grid_x][grid_y], vec2(x, y));
	GLfloat n1 = dot(grads[grid_x + 1][grid_y + 1], vec2(x, y));
	GLfloat ix0 = lerp(n0, n1, x - (float) grid_x);

	n0 = dot(grads[grid_x][grid_y], vec2(x, y));
	n1 = dot(grads[grid_x + 1][grid_y + 1], vec2(x, y));
	GLfloat ix1 = lerp(n0, n1, x - (float) grid_x);
	return lerp(ix0, ix1, y - (float) grid_y);
}