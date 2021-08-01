#include "PlayScene2.h"

#include "AttackBox.h"
#include "Background.h"
#include "CollisionManager.h"
#include "Config.h"
#include "EnemyKnight.h"
#include "LevelParser.h"
#include "EventManager.h"
#include "Game.h"
#include "Label.h"
#include "ScoreManager.h"
#include "SoundID.h"
#include "SoundManager.h"
#include "StateParser.h"
#include "TextureManager.h"

PlayScene2::PlayScene2() :
	m_state(SceneState::PLAY_SCENE2),
	m_score(0)
{
}

PlayScene2::~PlayScene2()
{
}

void PlayScene2::draw()
{
	SDL_SetRenderDrawColor(TextureManager::Instance().getRenderer(), 0, 0, 255, 255);
	Scene::drawDisplayList();

	//m_testPlayer->draw();
}

void PlayScene2::update()
{
	Scene::updateDisplayList();
	//m_testPlayer->update();
	if (m_score != nullptr)
	{
		m_score->setText("Score : " + std::to_string(ScoreManager::getScore()));
	}

	if (dynamic_cast<Napkin*>(getPlayer())->getGameOver())
	{
		TheGame::Instance().changeSceneState(SceneState::END_SCENE);
	}

	if (getGameClear())
	{
		TheGame::Instance().changeSceneState(SceneState::CLEAR_SCENE);
	}

	// Checking all Collisions
	auto displayList = getDisplayList();
	//std::cout << displayList.size() << std::endl;
	for (auto iterA = displayList.begin(); iterA != displayList.end();)
	{
		DisplayObject* objA = *iterA;
		iterA++;
		for (auto iterB = iterA; iterB != displayList.end(); iterB++)
		{

			DisplayObject* objB = *iterB;
			if (objA->getType() != GameObjectType::NONE && objB->getType() != GameObjectType::NONE)
			{
				if (objA->getType() != objB->getType())
				{
					if (CollisionManager::AABBCheckByRealCollisionBox(objA, objB))
					{
						objA->collision(objB);
						objB->collision(objA);
					}
				}
			}
		}
	}


}

void PlayScene2::clean()
{
}

bool PlayScene2::onExit()
{
	removeOnlyInList(dynamic_cast<DisplayObject*>(getPlayer()));
	Scene::removeAllChildren();
	SoundManager::Instance().clear();
	return true;
}

void PlayScene2::handleEvents()
{
	EventManager::Instance().update();

	// Keyboard Events
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance().quit();
	}
}

bool PlayScene2::onEnter()
{
	ScoreManager::resetScore();
	// texture loading
	StateParser stateParser;
	stateParser.ParseState(Config::TEXTURE_LOCATION.c_str(), Config::PLAY_SCENE2);

	SoundManager::Instance().playMusic(SoundID::BGM);


	Background* background = new Background(SceneState::PLAY_SCENE2);
	addChild(background);

	LevelParser levelParser;
	Level*  level = levelParser.ParseLevel(Config::SCENE2_LOCATION.c_str(), this);
	addChild(level);

	m_score = new Label("Score : ", "Consolas", 30, { 0, 255, 0, 255 }, glm::vec2(1000, 50.0f));
	addChild(m_score);


	/*Napkin* player = new Napkin(LoaderParams(100, 400, 80, 70, 40, 70, 100, 20, "napkin"));
	addChild(player, 1);*/


	//EnemyKnight* enemy = new EnemyKnight(glm::vec2(300, 0), 200, 10, level->getCollisionLayers());
	//addChild(enemy);


	//addChild(new AttackBox(SDL_Rect{ 100,100,100,100 }, glm::vec2(10, 0), 100));

	//setPlayer(player);
	setLevel(level);
	getDoor()->setEnabled(true);
	return true;
}

SceneState PlayScene2::getState()
{
	return m_state;
}
