#ifndef STATE_MAIN_MENU_H
#define STATE_MAIN_MENU_H


#include "game_state.h"
#include "input_manager.h"
#include "render_engine.h"

class StateMainMenu : public GameState {
private:
	InputManager* input_manager;
	RenderEngine* render_engine;
	GLFWwindow* window;

public:
	StateMainMenu(InputManager* input_manager, RenderEngine* render_engine, GLFWwindow* window);
	~StateMainMenu();

	void update();
	void render();
};

#endif