#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <glew/glew.h>

class GameState {
private:
public:
	virtual void update() = 0;
	virtual void render() = 0;
};

#endif