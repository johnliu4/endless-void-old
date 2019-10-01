#ifndef TERRAIN_H
#define TERRAIN_H

#include <glew/glew.h>

#include "perlin.h"

class Terrain {
private:
	int width, height;
	PerlinNoise perlin_noise;

	GLuint vertex_buffer;
	GLuint norm_buffer;

	int num_verts;
public:
	Terrain(const int width, const int height);
	~Terrain();
	void render();
};

#endif