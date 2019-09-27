#ifndef GAME_STATE_H
#define GAME_STATE_H

class GameState {
private:

public:
	virtual void render() = 0;
	virtual void update() = 0;
};

#endif