#include "state_ingame.h"

StateIngame::StateIngame() : terrain(200, 200) {
}

StateIngame::~StateIngame() {}

void StateIngame::update() {
	camera.update();
}

void StateIngame::render() {
	camera.render();
	terrain.render();
}