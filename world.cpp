#include "world.h"

#include "crate.h"

World::World(InputManager* input_manager, PhysicsEngine* physics_engine, RenderEngine* render_engine) {
	this->input_manager = input_manager;
	this->physics_engine = physics_engine;
	this->render_engine = render_engine;
	entity_manager = new EntityManager(physics_engine, render_engine);
	entity_manager->add_entity(new Crate(glm::vec3(0.0f, 0.0f, 0.0f), 1.0f));

	input_manager->center_cursor();
	world_scene = new Scene();
	render_engine->add_scene(world_scene);

	player = new Player(input_manager, physics_engine, world_scene,
		glm::vec3(0.0f, 3.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f));

	crate = new Crate(glm::vec3(0.0f, 0.5f, 0.0f), 1.0f);
	world_scene->add_entity(&(crate->get_scene_entity()));
	physics_engine->add_static_aabb(&(crate->get_bounding_box()));

	path_generator = new PathGenerator(player, physics_engine, world_scene);
}

World::~World() {
	delete entity_manager;
	delete player;
	delete crate;
	delete path_generator;

	render_engine->remove_scene(world_scene);
	delete world_scene;
}

void World::update() {
	player->update();
	physics_engine->update();
	path_generator->update();
}

void World::render() {
	render_engine->render();
	/*player->render();
	terrain->render();
	for (auto it = entity_manager->it_begin(); it != entity_manager->it_end(); it++) {
		(*it)->render();
	}*/
}
