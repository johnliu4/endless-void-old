#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/random.hpp>

#include <iostream>

#include "perlin.h"

using glm::vec2;
using glm::dot;
using glm::diskRand;

PerlinNoise::PerlinNoise() {
	grads = nullptr;
	width = 0;
	height = 0;
}

PerlinNoise::~PerlinNoise() {
	clear();
}

void PerlinNoise::clear() {
	if (grads != nullptr) {
		for (int x = 0; x < width; x++) {
			delete[] grads[x];
		}

		delete[] grads;
	}
}

void PerlinNoise::generate(const int width, const int height) {
	if (grads != nullptr) {
		clear();
	}

	// initialize 2d array of vectors to a random 2d unit vector
	grads = new vec2 * [width];
	for (int x = 0; x < width; x++) {
		grads[x] = new vec2[height];
	}

	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			grads[x][y] = diskRand(1.0f);
		}
	}

	this->width = width;
	this->height = height;
}

GLfloat lerp(GLfloat a0, GLfloat a1, GLfloat w) {
	return (1.0f - w) * a0 + w * a1;
}

GLfloat PerlinNoise::cosine_interp(GLfloat n1, GLfloat n2, GLfloat mu) {
	GLfloat mu2 = (1.0f - glm::cos(mu * glm::pi<GLfloat>())) / 2.0f;
	return (n1 * (1.0f - mu2) + n2 * mu2);
}

// gets a Perlin value at a coordinate 
GLfloat PerlinNoise::get_value(GLfloat x, GLfloat y) {
	if (grads == nullptr) {
		return 0.0f;
	}

	// find the grid coordinates the Perlin coordinates belong to
	int grid_x = (int)x;
	int grid_y = (int)y;
	// ensure they are not out of bounds
	if (grid_x < 0 || grid_y < 0 || grid_x > width - 1 || grid_y > height - 1) {
		return 0.0f;
	}

	if (grid_x == width - 1) {
		grid_x -= 1;
	}

	if (grid_y == height - 1) {
		grid_y -= 1;
	}

	GLfloat n0 = dot(grads[grid_x][grid_y], vec2(x, y));
	GLfloat n1 = dot(grads[grid_x + 1][grid_y], vec2(x, y));
	GLfloat ix0 = cosine_interp(n0, n1, x - (float) grid_x);

	n0 = dot(grads[grid_x][grid_y + 1], vec2(x, y));
	n1 = dot(grads[grid_x + 1][grid_y + 1], vec2(x, y));
	GLfloat ix1 = cosine_interp(n0, n1, x - (float) grid_x);
	return cosine_interp(ix0, ix1, y - (float) grid_y);
}