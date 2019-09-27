#ifndef TERRAIN_H
#define TERRAIN_H

#include <glew/glew.h>

class Terrain {
private:
	GLuint vertex_buffer;
public:
	Terrain();
	~Terrain();
	void render();
};

#endif