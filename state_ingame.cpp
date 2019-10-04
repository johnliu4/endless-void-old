#include "state_ingame.h"

StateIngame::StateIngame() {
	world = new World();
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