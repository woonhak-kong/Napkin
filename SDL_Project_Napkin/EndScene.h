#pragma once
#ifndef __END_SCENE__
#define __END_SCENE__
#include "Level.h"
#include "Napkin.h"
#include "Scene.h"
class EndScene : public Scene
{
public:
	EndScene();
	~EndScene();

	// Inherited via Scene
	void draw() override;
	void update() override;
	void clean() override;
	bool onExit() override;
	void handleEvents() override;
	bool onEnter() override;

	SceneState getState() override;

private:

	SceneState m_state;
};

#endif // __END_SCENE__
