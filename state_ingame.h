#ifndef STATE_INGAME_H
#define STATE_INGAME_H

#include "game_state.h"
#include "world.h"

class StateIngame : public GameState {
private:
	World* world;
public:

	StateIngame();
	~StateIngame();
	void render();
	void update();
};

#endif