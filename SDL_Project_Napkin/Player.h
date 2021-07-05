
#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "SDL.h"

#define DELTA_TIME

#define MAX_JUMP_HEIGHT

enum Facing { LEFT = -1, RIGHT = 1 };
enum State { IDLING, RUNNING, JUMPING, FALLING, HURTING, ATTACKING, DYING };

class Player : public GameObject
{
public:
	Player();
	virtual ~player() {}

	virtual void draw();
	virtual void update();
	virtual void clean();

private:
	void idle();
	void run();
	void jump();
	void fall();
	void hurt();
	void dead();
	void attack();

	void inputs();
	void setState(State state, std::string textureID, int numFrame, unsigned int deltaTime = DELTA_TIME);

	Facing m_dir;
	State m_state :
	unsigned int m_deltaTime;

	std::string m_textureID;
	SDL_RenderFlip m_flip;
	int m_row, m_frame, m_numFrame;

	bool m_canJump;
	bool m_keyIsAlreadyPressed;
	Vector2D m_lastSafePos;
};

#endif