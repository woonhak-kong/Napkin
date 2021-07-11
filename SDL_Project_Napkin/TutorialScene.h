#pragma once
#ifndef __TUTORIAL_SCENE__
#define __TUTORIAL_SCENE__
#include "Label.h"
#include "Scene.h"
class TutorialScene : public Scene
{
public:
	TutorialScene();
	~TutorialScene();

	void draw() override;
	void clean() override;
	void update() override;
	bool onExit() override;
	void handleEvents() override;
	bool onEnter() override;
	SceneState getState() override;

private:
	Label* m_score;

	SceneState m_state;
};

#endif // __TUTORIAL_SCENE__