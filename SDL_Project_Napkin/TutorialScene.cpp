#include "TutorialScene.h"

#include "Background.h"
#include "CollisionManager.h"
#include "EventManager.h"
#include "Game.h"
#include "Napkin.h"
#include "ScoreManager.h"
#include "TextureManager.h"
#include "SoundManager.h"
#include "StateParser.h"
#include "LevelParser.h"
#include "SoundID.h"

TutorialScene::TutorialScene() :
	m_state(SceneState::TUTORIAL_SCENE),
	m_score(0)
{
}

TutorialScene::~TutorialScene()
{
}

void TutorialScene::draw()
{
	SDL_SetRenderDrawColor(TextureManager::Instance().getRenderer(), 0, 0, 255, 255);
	Scene::drawDisplayList();
}

void TutorialScene::clean()
{
}

void TutorialScene::update()
{
	Scene::updateDisplayList();
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
		TheGame::Instance().changeSceneState(SceneState::PLAY_SCENE1);
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
				if (objA->isEnabled() && objB->isEnabled())
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


}

bool TutorialScene::onExit()
{
	std::cout << "Tutorial Scene on exit" << std::endl;
	removeOnlyInList(dynamic_cast<DisplayObject*>(getPlayer()));
	Scene::removeAllChildren();
	SoundManager::Instance().clear();
	return true;
}

void TutorialScene::handleEvents()
{
	EventManager::Instance().update();

	// Keyboard Events
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance().quit();
	}
}

bool TutorialScene::onEnter()
{
	ScoreManager::resetScore();

	StateParser stateParser;
	stateParser.ParseState(Config::TEXTURE_LOCATION.c_str(), Config::TUTORIAL_SCENE);

	SoundManager::Instance().playMusic(SoundID::BGM);

	Background* background = new Background(SceneState::TUTORIAL_SCENE);
	addChild(background);

	LevelParser levelParser;
	Level* level = levelParser.ParseLevel(Config::SCENE0_LOCATION.c_str(), this);
	addChild(level);

	m_score = new Label("Score : ", "Consolas", 30, { 0, 255, 0, 255 }, glm::vec2(1000, 50.0f));
	addChild(m_score);

	Label* moveExplanation = new Label("You can move by clicking '<-'  '->' ", "Consolas", 20, { 255, 255, 0, 255 },
		glm::vec2(80, 500.0f), 0, false, true);
	addChild(moveExplanation);

	Label* hpExplanation = new Label("-This is your HP-", "Consolas", 20, { 255, 255, 0, 255 },
		glm::vec2(80, 60.0f), 0, false);
	addChild(hpExplanation);

	Label* scoreExplanation = new Label("You can get a score by killing enemies --> ", "Consolas", 20, { 255, 255, 0, 255 },
		glm::vec2(450, 40.0f), 0, false);
	addChild(scoreExplanation);

	Label* doubleJumpExplanation = new Label("You can double jump by clicking 'Space' twice ", "Consolas", 20, { 255, 255, 0, 255 },
		glm::vec2(400, 300.0f), 0, false, true);
	addChild(doubleJumpExplanation);

	Label* attackExplanation = new Label("You can attack by clicking 'F'", "Consolas", 20, { 255, 255, 0, 255 },
		glm::vec2(900, 500.0f), 0, false, true);
	addChild(attackExplanation);

	Label* hitExplanation = new Label("If you're hit by enemies, HP will be reduced.", "Consolas", 20, { 255, 55, 0, 255 },
		glm::vec2(1100, 400.0f), 0, false, true);
	addChild(hitExplanation);

	Label* gateExplanation = new Label("The gate sends you to next level", "Consolas", 20, { 255, 180, 0, 255 },
		glm::vec2(2000, 200.0f), 0, false, true);
	addChild(gateExplanation);


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

SceneState TutorialScene::getState()
{
	return m_state;
}
