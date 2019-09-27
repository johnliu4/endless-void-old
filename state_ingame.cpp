#include "state_ingame.h"

StateIngame::StateIngame() {}

StateIngame::~StateIngame() {}

void StateIngame::update() {
	camera.update();
}

void StateIngame::render() {
	camera.render();
	terrain.render();
}