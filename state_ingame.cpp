#include "state_ingame.h"

StateIngame::StateIngame(InputManager* input_manager, PhysicsEngine* physics_engine, RenderEngine* render_engine) {
	this->input_manager = input_manager;
	this->physics_engine = physics_engine;
	this->render_engine = render_engine;
	world = new World(input_manager, physics_engine, render_engine);
}

StateIngame::~StateIngame() {
	delete world;
}

void StateIngame::update() {
	world->update();
}

void StateIngame::render() {
	world->render();
}