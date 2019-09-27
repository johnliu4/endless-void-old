#ifndef STATE_INGAME_H
#define STATE_INGAME_H

#include "game_state.h"
#include "camera.h"
#include "terrain.h"

class StateIngame : public GameState {
private:
	Camera camera;
	Terrain terrain;
public:
	StateIngame();
	~StateIngame();
	void render();
	void update();
};

#endif