#include "StartScene.h"
#include <algorithm>

#include "Button.h"
#include "Game.h"
#include "glm/gtx/string_cast.hpp"
#include "EventManager.h"
#include "Label.h"
#include "LevelParser.h"
#include "SoundID.h"
#include "StateParser.h"
#include "TextureManager.h"
#include "SoundManager.h"
#include "TextureID.h"


StartScene::StartScene() :
	m_state(SceneState::START_SCENE)
{
	SoundManager::Instance().load("assets/sounds/bgm/start scene.mp3", "bgm", SoundType::SOUND_MUSIC);
	SoundManager::Instance().playMusic("bgm", 10, 0);
	SoundManager::Instance().setMusicVolume(30);

}

StartScene::~StartScene()
= default;

void StartScene::draw()
{
	SDL_SetRenderDrawColor(TextureManager::Instance().getRenderer(), 0, 0, 255, 255);
	TextureManager::Instance().draw(TextureID::MAIN_BG, 0, 0, Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT);
	Scene::drawDisplayList();
}

void StartScene::update()
{
	Scene::updateDisplayList();
}

void StartScene::clean()
{

}

bool StartScene::onExit()
{
	Scene::removeAllChildren();
	//SoundManager::Instance().clear();
	return true;
}

void StartScene::handleEvents()
{
	EventManager::Instance().update();

	// Keyboard Events
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance().quit();
	}

}

bool StartScene::onEnter()
{
	delete Game::Instance().getPlayer();
	Game::Instance().setPlayer(nullptr);
	//const SDL_Color blue = { 0, 0, 255, 255 };
	StateParser stateParser;
	stateParser.ParseState(Config::TEXTURE_LOCATION.c_str(), Config::START_SCENE);

	//SoundManager::Instance().playMusic(SoundID::BGM);


	/*Label* name = new Label("Napkin", "Consolas", 200, {0, 255, 0, 255}, glm::vec2(Config::SCREEN_WIDTH /2, 120.0f));
	addChild(name);*/

	m_pSartButton = new Button("assets/UI/PlayButton.png", "startbutton", GameObjectType::START_BUTTON,
		glm::vec2(Config::SCREEN_WIDTH / 2, Config::SCREEN_HEIGHT / 2), true);

	m_pSartButton->addEventListener(Event::CLICK, [&]()-> void
		{
			SoundManager::Instance().playSound(SoundID::BTN_CLICK);
			Game::Instance().changeSceneState(SceneState::TUTORIAL_SCENE);

		});
	m_pSartButton->addEventListener(Event::MOUSE_OVER, [&]() -> void
		{
			m_pSartButton->setAlpha(150);
			SoundManager::Instance().playSound(SoundID::BTN_HOVER);
		});

	m_pSartButton->addEventListener(Event::MOUSE_OUT, [&]() -> void
		{
			m_pSartButton->setAlpha(255);
		});

	addChild(m_pSartButton);

	m_pExitButton = new Button("assets/UI/ExitButton.png", "exitbutton", GameObjectType::EXIT_BUTTON,
		glm::vec2(Config::SCREEN_WIDTH / 2, Config::SCREEN_HEIGHT / 2 + 120), true);
	m_pExitButton->addEventListener(Event::CLICK, [&]() -> void
		{
			SoundManager::Instance().playSound(SoundID::BTN_CLICK);
			TheGame::Instance().quit();
		});
	m_pExitButton->addEventListener(Event::MOUSE_OVER, [&]() -> void
		{
			m_pExitButton->setAlpha(150);
			SoundManager::Instance().playSound(SoundID::BTN_HOVER);
		});

	m_pExitButton->addEventListener(Event::MOUSE_OUT, [&]() -> void
		{
			m_pExitButton->setAlpha(255);
		});

	addChild(m_pExitButton);

	return true;
}

SceneState StartScene::getState()
{
	return m_state;
}

