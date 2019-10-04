#include "world.h"

World::World() {
	player = new Player(glm::vec3(0.0f, 5.0f, 0.0f), glm::vec3(1.0f, -0.5f, 0.5f));
	terrain = new Terrain(200, 200);
}

World::~World() {
	delete player;
	delete terrain;
}

void World::update() {
	player->update();
}

void World::render() {
	player->render();
	terrain->render();
}