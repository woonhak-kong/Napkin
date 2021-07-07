#include "PlayScene1.h"

#include "AttackBox.h"
#include "Background.h"
#include "CollisionManager.h"
#include "Config.h"
#include "EnemyKnight.h"
#include "LevelParser.h"
#include "EventManager.h"
#include "Game.h"
#include "SoundManager.h"
#include "StateParser.h"
#include "TextureManager.h"

PlayScene1::PlayScene1() :
	m_state(SceneState::PLAY_SCENE1)
{
}

PlayScene1::~PlayScene1()
{
}

void PlayScene1::draw()
{
	SDL_SetRenderDrawColor(TextureManager::Instance().getRenderer(), 0, 0, 255, 255);
	Scene::drawDisplayList();

	//m_testPlayer->draw();
}

void PlayScene1::update()
{
	Scene::updateDisplayList();
	//m_testPlayer->update();

	if (getPlayer()->getTransform().getPosition().y > Config::SCREEN_HEIGHT)
	{
		TheGame::Instance().changeSceneState(SceneState::END_SCENE);
	}

	// Checking all Collisions
	auto displayList = getDisplayList();
	for (std::vector<DisplayObject*>::iterator iterA = displayList.begin(); iterA != displayList.end();)
	{
		DisplayObject* objA = *iterA;
		iterA++;
		for (std::vector<DisplayObject*>::iterator iterB = iterA; iterB != displayList.end(); iterB++)
		{
			DisplayObject* objB = static_cast<DisplayObject*>(*iterB);
			if (objA->getType() == GameObjectType::PLAYER_ATTACK && objB->getType() == GameObjectType::ENEMY)
			{
				if (CollisionManager::AABBCheckByRealCollisionBox(objA, objB))
				{
					//std::cout << "collsion!!!\n" << std::endl;
					dynamic_cast<Character*>(objB)->takeDamage(dynamic_cast<AttackBox*>(objA)->getAttackPower());
					dynamic_cast<AttackBox*>(objA)->deleteAttackBox();
				}
			}
		}
	}

}

void PlayScene1::clean()
{
}

bool PlayScene1::onExit()
{
	Scene::removeAllChildren();
	return true;
}

void PlayScene1::handleEvents()
{
	EventManager::Instance().update();

	// Keyboard Events
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance().quit();
	}
}

bool PlayScene1::onEnter()
{
	// texture loading
	StateParser stateParser;
	stateParser.ParseState(Config::TEXTURE_LOCATION.c_str(), Config::PLAY_SCENE2);

	SoundManager::Instance().playMusic("bgm");


	Background* background = new Background();
	addChild(background);

	LevelParser levelParser;
	Level*  level = levelParser.ParseLevel("assets/maps/scene1.tmx", this);
	addChild(level);


	Napkin* player = new Napkin(LoaderParams(0, 0, 80, 70, 40, 70, 300, 20, "napkin"));
	addChild(player);


	//EnemyKnight* enemy = new EnemyKnight(glm::vec2(300, 0), 200, 10, level->getCollisionLayers());
	//addChild(enemy);


	//addChild(new AttackBox(SDL_Rect{ 100,100,100,100 }, glm::vec2(10, 0), 100));

	setPlayer(player);
	setLevel(level);

	return true;
}

SceneState PlayScene1::getState()
{
	return m_state;
}
