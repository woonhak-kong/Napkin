#include "EndScene.h"

#include "Button.h"
#include "EventManager.h"
#include "Game.h"
#include "Label.h"

EndScene::EndScene() :
	m_state(SceneState::END_SCENE)
{
}

EndScene::~EndScene()
{
}

void EndScene::draw()
{
	Scene::drawDisplayList();
}

void EndScene::update()
{
	Scene::updateDisplayList();
}

void EndScene::clean()
{
}

bool EndScene::onExit()
{
	Scene::removeAllChildren();
	return true;
}

void EndScene::handleEvents()
{
	EventManager::Instance().update();

	// Keyboard Events
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance().quit();
	}
}

bool EndScene::onEnter()
{
	Label* gameOver = new Label("Game Over", "lazy", 200, { 255,0,0,255 }, glm::vec2(Config::SCREEN_WIDTH / 2, 120.0f));
	addChild(gameOver);

	Button* menuButton = new Button("assets/UI/MenuButton.png", "menubutton", GameObjectType::MENU_BUTTON,
		glm::vec2(Config::SCREEN_WIDTH / 2, Config::SCREEN_HEIGHT / 2), true);
	menuButton->addEventListener(Event::CLICK, [&]() -> void
		{
			TheGame::Instance().changeSceneState(SceneState::START_SCENE);
		});
	addChild(menuButton);

	Button* exitButton = new Button("assets/UI/ExitButton.png", "exitbutton", GameObjectType::EXIT_BUTTON,
		glm::vec2(Config::SCREEN_WIDTH / 2, Config::SCREEN_HEIGHT / 2 + 120), true);
	exitButton->addEventListener(Event::CLICK, [&]() -> void
		{
			TheGame::Instance().quit();
		});
	addChild(exitButton);

	return true;
}

SceneState EndScene::getState()
{
	return m_state;
}

