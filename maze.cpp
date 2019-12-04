#include <cstdlib>
#include <list>
#include <glm/gtc/constants.hpp>

#include "maze.h"
#include "obj_loader.h"

GLuint Maze::wall_vertex_buffer_id = 0;
GLuint Maze::wall_uv_buffer_id = 0;
GLuint Maze::wall_num_vertices = 0;
bool Maze::wall_scene_entity_init = false;

// an auxiliary data structure for use in the generation algorithm
struct MazeWall {
	int x;
	int y;
	MazeDirection dir;
};

Maze::Maze() {
	walls = nullptr;
	rand_seed = 0;
	width = 0;
	height = 0;
	init = false;
	num_walls = 0;

	if (!wall_scene_entity_init) {
		//load_obj("./resources/maze_wall.obj", wall_num_vertices, wall_vertex_buffer_id, wall_uv_buffer_id);
		wall_scene_entity_init = true;
	}

	wall_scene_entities = nullptr;
}

Maze::Maze(int width, int height) : Maze() {
	this->width = width;
	this->height = height;
}

Maze::Maze(int width, int height, unsigned int rand_seed) : Maze() {
	this->rand_seed = rand_seed;
	this->width = width;
	this->height = height;
}

Maze::~Maze() {
	// free up 2d array of maze cells
	if (init) {
		for (int x = 0; x < width; x++) {
			delete[] walls[x];
		}

		delete walls;
	}
}

bool Maze::is_valid(int x, int y) {
	return x >= 0 && y >= 0 && x < width && y < height;
}

bool Maze::is_wall(int x, int y, MazeDirection dir) {
	// borders of the maze are always walls
	if ((x == 0 && dir == LEFT)
		|| (y == 0 && dir == UP)
		|| (x == width - 1 && dir == RIGHT)
		|| (y == height - 1 && dir == DOWN)
	) {
		return true;
	}

	if (dir == UP) {
		return walls[x][y].top_wall;
	} else if (dir == LEFT) {
		return walls[x][y].left_wall;
	} else if (dir == DOWN) {
		return walls[x][y + 1].top_wall;
	} else {
		return walls[x + 1][y].left_wall;
	}
}

void Maze::remove_wall(int x, int y, MazeDirection dir) {
	if (dir == UP) {
		walls[x][y].top_wall = false;
	} else if (dir == LEFT) {
		walls[x][y].left_wall = false;
	} else if (dir == DOWN) {
		walls[x][y + 1].top_wall = false;
	} else {
		walls[x + 1][y].left_wall = false;
	}
}

// generates a maze using a randomized version of Prim's MST algorithm
void Maze::generate(Scene* render_scene, PhysicsEngine* physics_engine) {
	// reformat the current maze if it exists already
	if (init) {
		for (int x = 0; x < width; x++) {
			for (int y = 0; y < width; y++) {
				walls[x][y].top_wall = true;
				walls[x][y].left_wall = true;
			}
		}
	} else {
		walls = new MazeCell*[width];
		for (int x = 0; x < width; x++) {
			walls[x] = new MazeCell[height];
		}
	}

	// keep track of cells that we have visited
	bool** visited = new bool*[width];
	for (int x = 0; x < width; x++) {
		visited[x] = new bool[height] {false};
	}

	// set the upper left cell to be the maze entry
	maze_start = glm::ivec2(0, 0);
	walls[0][0].top_wall = false;
	walls[0][0].left_wall = false;
	visited[0][0] = true;
	std::list<MazeWall> walls_list;
	walls_list.push_back({ 0, 0, DOWN });
	walls_list.push_back({ 0, 0, RIGHT });

	while (walls_list.size() > 0) {
		// choose a random wall from the list of walls
		int idx = std::rand() % walls_list.size();
		std::list<MazeWall>::iterator it = walls_list.begin();
		for (int i = 0; i < idx; i++) {
			it++; 
		}

		// find the previous cell that is was connected to
		MazeWall& wall = *it;
		MazeWall prev_wall = { wall.x, wall.y };
		if (wall.dir == UP) {
			prev_wall.y -= 1;
		} else if (wall.dir == LEFT) {
			prev_wall.x -= 1;
		} else if (wall.dir == DOWN) {
			prev_wall.y += 1;
		} else {
			prev_wall.x += 1;
		}

		// if only one of the cells that the wall divides has been visited
		// then remove this wall
		if (!(visited[wall.x][wall.y] && visited[prev_wall.x][prev_wall.y])) {
			remove_wall(wall.x, wall.y, wall.dir);
			visited[wall.x][wall.y] = true;
			// then check the adjacent cells and add them to the wall list if possible
			if (is_valid(wall.x, wall.y - 1) && !visited[wall.x][wall.y - 1]) { // up
				walls_list.push_back({ wall.x, wall.y - 1, DOWN });
			}
			
			if (is_valid(wall.x - 1, wall.y) && !visited[wall.x - 1][wall.y]) { // left
				walls_list.push_back({ wall.x - 1, wall.y, RIGHT });
			}
			
			if (is_valid(wall.x, wall.y + 1) && !visited[wall.x][wall.y + 1]) { // down
				walls_list.push_back({ wall.x, wall.y + 1, UP });
			}
			
			if (is_valid(wall.x + 1, wall.y) && !visited[wall.x + 1][wall.y]) { // right
				walls_list.push_back({ wall.x + 1, wall.y, LEFT });
			}
		}

		walls_list.erase(it);
	}

	num_walls = 0;
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			num_walls += walls[x][y].top_wall;
			num_walls += walls[x][y].left_wall;
		}
	}

	// randomly choose a cell along the lowest row or rightmost column to be the maze end
	//const int right_wall_end = std::rand() % 2;
	//if (right_wall_end) {
	//	maze_end = glm::ivec2(width - 1, std::rand() % height);
	//} else {
	//	maze_end = glm::ivec2(std::rand() % width, height - 1);
	//}

	//// add the lowest row and right-most column of walls, and subtract one wall for the maze end
	num_walls += width + height;

	// add all the walls to the render engine
	wall_scene_entities = new SceneEntity*[num_walls];
	int wall_count = 0;
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			if (walls[x][y].top_wall) {
				wall_scene_entities[wall_count] = new SceneEntity(wall_vertex_buffer_id, wall_num_vertices);
				wall_scene_entities[wall_count]->set_pos(glm::vec3(x * 2.0f + 1.0f, 0.0f, y * 2.0f));
				wall_scene_entities[wall_count]->set_rotation_axis(glm::vec3(0.0f, 1.0f, 0.0f));
				wall_scene_entities[wall_count]->set_rotation_angle(glm::half_pi<GLfloat>());
				render_scene->add_entity(wall_scene_entities[wall_count]);
				wall_count++;
			}

			if (walls[x][y].left_wall) {
				wall_scene_entities[wall_count] = new SceneEntity(wall_vertex_buffer_id, wall_num_vertices);
				wall_scene_entities[wall_count]->set_pos(glm::vec3(x * 2.0f, 0.0f, y * 2.0f + 1.0f));
				render_scene->add_entity(wall_scene_entities[wall_count]);
				wall_count++;
			}
		}
	}

	// add lowest row of walls
	for (int x = 0; x < width; x++) {
		wall_scene_entities[wall_count] = new SceneEntity(wall_vertex_buffer_id, wall_num_vertices);
		wall_scene_entities[wall_count]->set_pos(glm::vec3(x * 2.0f + 1.0f, 0.0f, height * 2.0f));
		wall_scene_entities[wall_count]->set_rotation_axis(glm::vec3(0.0f, 1.0f, 0.0f));
		wall_scene_entities[wall_count]->set_rotation_angle(glm::half_pi<GLfloat>());
		render_scene->add_entity(wall_scene_entities[wall_count]);
		wall_count++;
	}

	// add rightmost of walls
	for (int y = 0; y < height; y++) {
		wall_scene_entities[wall_count] = new SceneEntity(wall_vertex_buffer_id, wall_num_vertices);
		wall_scene_entities[wall_count]->set_pos(glm::vec3(width * 2.0f, 0.0f, y * 2.0f + 1.0f));
		render_scene->add_entity(wall_scene_entities[wall_count]);
		wall_count++;
	}


	/*
	std::stringstream first_row;
	for (int x = 0; x < width; x++) {
		if (walls[x][0].top_wall) {
			first_row << " _";
		} else {
			first_row << "  ";
		}
	}

	std::cout << first_row.str() << std::endl;

	for (int y = 1; y < height; y++) {
		std::stringstream ss;
		for (int x = 0; x < width; x++) {
			if (walls[x][y - 1].left_wall) {
				ss << "|";
			} else {
				ss << " ";
			}

			if (walls[x][y].top_wall) {
				ss << "_";
			} else {
				ss << " ";
			}
		}

		std::cout << ss.str() << std::endl;
	}

	std::stringstream last_row;
	for (int x = 0; x < width; x++) {
		if (walls[x][height - 1].left_wall) {
			last_row << "| ";
		} else {
			last_row << "  ";
		}
	}

	std::cout << last_row.str() << std::endl;
	*/

}

void Maze::set_width(int width) {
	this->width = width;
}

void Maze::set_height(int height) {
	this->height = height;
}

void Maze::set_rand_seed(unsigned int rand_seed) {
	this->rand_seed = rand_seed;
}

int Maze::get_width() {
	return width;
}

int Maze::get_height() {
	return height;
}

glm::ivec2 Maze::get_maze_start() {
	return maze_start;
}

glm::ivec2 Maze::get_maze_end() {
	return maze_end;
}