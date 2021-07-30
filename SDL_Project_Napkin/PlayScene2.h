#pragma once
#ifndef __PLAY__SCENE2__
#define __PLAY__SCENE2__
#include "Level.h"
#include "Napkin.h"
#include "Scene.h"
class Label;

class PlayScene2 : public Scene
{
public:
	PlayScene2();
	~PlayScene2();

	// Inherited via Scene
	void draw() override;
    void update() override;
    void clean() override;
	bool onExit() override;
	void handleEvents() override;
	bool onEnter() override;

	SceneState getState() override;

private:

	Label* m_score;

	SceneState m_state;
};

#endif // __PLAY__SCENE1__
