#include "state_in_game.h"

StateInGame::StateInGame(InputManager* input_manager, PhysicsEngine* physics_engine, RenderEngine* render_engine) {
	this->input_manager = input_manager;
	this->physics_engine = physics_engine;
	this->render_engine = render_engine;
	world = new World(input_manager, physics_engine, render_engine);
}

StateInGame::~StateInGame() {
	delete world;
}

void StateInGame::update() {
	world->update();
}

void StateInGame::render() {
	world->render();
}