#ifndef MAZE_H
#define MAZE_H

#include <glew/glew.h>

#include "physics_engine.h"
#include "scene.h"
#include "scene_entity.h"

/* A random maze generator. */

/*
 * Each maze cell will contain information about its top and left walls.
 * This lets us represent a grid of walls easily. The only thing to note
 * is that this means the bottom-most and right-most cells will not have
 * bottom and right walls respectively. When rendering and updating,
 * do not forget to manually include the bottom-most and right-most walls.
 */
struct MazeCell {
	bool top_wall = true;
	bool left_wall = true;
};



enum MazeDirection { UP, LEFT, DOWN, RIGHT };

class Maze {
private:
	MazeCell** walls;
	int num_walls;

	unsigned int rand_seed;
	int width;
	int height;

	// whether or not the maze has been generated yet
	bool init;
	
	// determines if the given coordinates are valid
	bool is_valid(int x, int y);
	bool is_wall(int x, int y, MazeDirection dir);
	void remove_wall(int x, int y, MazeDirection dir);

	// positions of the cells that represent the maze ends
	// the points will be along the borders
	glm::ivec2 maze_start;
	glm::ivec2 maze_end;

	static GLuint wall_vertex_buffer_id;
	static GLuint wall_uv_buffer_id;
	static GLuint wall_num_vertices;
	static bool wall_scene_entity_init;

	SceneEntity** wall_scene_entities;

public:
	Maze();
	Maze(int width, int height);
	Maze(int width, int height, unsigned int rand_seed);
	~Maze();
	
	// generates a random maze according to the random seed
	void generate(Scene* render_scene, PhysicsEngine* physics_engine);

	void set_width(int width);
	void set_height(int height);
	void set_rand_seed(unsigned int rand_seed);

	int get_width();
	int get_height();
	
	glm::ivec2 get_maze_start();
	glm::ivec2 get_maze_end();
};

#endif