#ifndef STATE_INGAME_H
#define STATE_INGAME_H

#include "game_state.h"
#include "world.h"
#include "input_manager.h"
#include "physics_engine.h"
#include "render_engine.h"

class StateIngame : public GameState {
private:
	InputManager* input_manager;
	PhysicsEngine* physics_engine;
	RenderEngine* render_engine;

	World* world;
public:
	StateIngame(InputManager* input_manager, PhysicsEngine* physics_engine, RenderEngine* render_engine);
	~StateIngame();
	void update();
	void render();
};

#endif