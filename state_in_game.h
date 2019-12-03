#ifndef STATE_IN_GAME_H
#define	STATE_IN_GAME_H

#include "game_state.h"
#include "world.h"
#include "input_manager.h"
#include "physics_engine.h"
#include "render_engine.h"

class StateInGame : public GameState {
private:
	InputManager* input_manager;
	PhysicsEngine* physics_engine;
	RenderEngine* render_engine;

	World* world;
public:
	StateInGame(InputManager* input_manager, PhysicsEngine* physics_engine, RenderEngine* render_engine);
	~StateInGame();
	void update();
	void render();
};

#endif