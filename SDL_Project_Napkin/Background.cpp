#include "Background.h"

#include "Camera.h"
#include "Character.h"
#include "CharacterState.h"
#include "Config.h"
#include "Game.h"
#include "Scene.h"
#include "TextureManager.h"

Background::Background(SceneState state):
	m_sceneState(state)
{
	switch (state)
	{
		case SceneState::TUTORIAL_SCENE:
			TextureManager::Instance().load("assets/maps/PixelPlatformerSet2v/Background/scene2/background1.png", "background1");
			TextureManager::Instance().load("assets/maps/PixelPlatformerSet2v/Background/scene2/background2.png", "background2");
			TextureManager::Instance().load("assets/maps/PixelPlatformerSet2v/Background/scene2/background3.png", "background3");
			TextureManager::Instance().load("assets/maps/PixelPlatformerSet2v/Background/scene2/background4.png", "background4");
			break;
		case SceneState::PLAY_SCENE1:
			TextureManager::Instance().load("assets/maps/PixelPlatformerSet2v/Background/scene1/background1.png", "background1");
			TextureManager::Instance().load("assets/maps/PixelPlatformerSet2v/Background/scene1/background2.png", "background2");
			TextureManager::Instance().load("assets/maps/PixelPlatformerSet2v/Background/scene1/background3.png", "background3");
			TextureManager::Instance().load("assets/maps/PixelPlatformerSet2v/Background/scene1/background4.png", "background4");
			TextureManager::Instance().load("assets/maps/PixelPlatformerSet2v/Background/scene1/background5.png", "background5");
			TextureManager::Instance().load("assets/maps/PixelPlatformerSet2v/Background/scene1/background6.png", "background6");
			break;
		case SceneState::PLAY_SCENE2:
			TextureManager::Instance().load("assets/maps/PixelPlatformerSet2v/Background/scene0/plx-1.png", "background1");
			TextureManager::Instance().load("assets/maps/PixelPlatformerSet2v/Background/scene0/plx-2.png", "background2");
			TextureManager::Instance().load("assets/maps/PixelPlatformerSet2v/Background/scene0/plx-3.png", "background3");
			TextureManager::Instance().load("assets/maps/PixelPlatformerSet2v/Background/scene0/plx-4.png", "background4");
			TextureManager::Instance().load("assets/maps/PixelPlatformerSet2v/Background/scene0/plx-5.png", "background5");

			break;
	}
	for (int i = 0; i < 6; i++)
	{
		m_speed[i] = (i + 1) * 10;
	}
	for (int& i : m_backgroudX1)
	{
		i = 0;
	}

	for (int& i : m_backgroudX2)
	{
		i = Config::SCREEN_WIDTH;
	}


	//setType(GameObjectType::NONE);
}

void Background::draw()
{
	switch (m_sceneState)
	{
		case SceneState::TUTORIAL_SCENE:
			TextureManager::Instance().draw("background1", m_backgroudX1[0], 0, Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT);
			TextureManager::Instance().draw("background1", m_backgroudX2[0], 0, Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT);
			TextureManager::Instance().draw("background2", m_backgroudX1[1], 0, Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT);
			TextureManager::Instance().draw("background2", m_backgroudX2[1], 0, Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT);
			TextureManager::Instance().draw("background3", m_backgroudX1[2], 0, Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT);
			TextureManager::Instance().draw("background3", m_backgroudX2[2], 0, Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT);
			TextureManager::Instance().draw("background4", m_backgroudX1[3], 0, Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT);
			TextureManager::Instance().draw("background4", m_backgroudX2[3], 0, Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT);
			break;
		case SceneState::PLAY_SCENE1:
			TextureManager::Instance().draw("background1", m_backgroudX1[0], 0, Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT);
			TextureManager::Instance().draw("background1", m_backgroudX2[0], 0, Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT);
			TextureManager::Instance().draw("background2", m_backgroudX1[1], 0, Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT);
			TextureManager::Instance().draw("background2", m_backgroudX2[1], 0, Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT);
			TextureManager::Instance().draw("background3", m_backgroudX1[2], 0, Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT);
			TextureManager::Instance().draw("background3", m_backgroudX2[2], 0, Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT);
			TextureManager::Instance().draw("background4", m_backgroudX1[3], 0, Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT);
			TextureManager::Instance().draw("background4", m_backgroudX2[3], 0, Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT);
			TextureManager::Instance().draw("background5", m_backgroudX1[4], 0, Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT);
			TextureManager::Instance().draw("background5", m_backgroudX2[4], 0, Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT);
			TextureManager::Instance().draw("background6", m_backgroudX1[5], 0, Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT);
			TextureManager::Instance().draw("background6", m_backgroudX2[5], 0, Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT);
			break;
		case SceneState::PLAY_SCENE2:
			TextureManager::Instance().draw("background1", m_backgroudX1[0], 0, Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT);
			TextureManager::Instance().draw("background1", m_backgroudX2[0], 0, Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT);
			TextureManager::Instance().draw("background2", m_backgroudX1[1], 0, Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT);
			TextureManager::Instance().draw("background2", m_backgroudX2[1], 0, Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT);
			TextureManager::Instance().draw("background3", m_backgroudX1[2], 0, Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT);
			TextureManager::Instance().draw("background3", m_backgroudX2[2], 0, Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT);
			TextureManager::Instance().draw("background4", m_backgroudX1[3], 0, Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT);
			TextureManager::Instance().draw("background4", m_backgroudX2[3], 0, Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT);
			TextureManager::Instance().draw("background5", m_backgroudX1[4], 0, Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT);
			TextureManager::Instance().draw("background5", m_backgroudX2[4], 0, Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT);
			break;
		default:
			break;
	}

}

void Background::update()
{
	auto player = getParent()->getPlayer();
	//auto camera = Camera::Instance().getPosition();


	float currX = Camera::Instance().getPosition().x;
	int direction = m_prevCameraX - currX;
	//left
	//direction = -3;
	float speedDirection = direction * Game::Instance().getDeltaTime();

	for (int i = 0; i < 6; i++)
	{
		m_backgroudX1[i] = m_backgroudX1[i] + (int)(m_speed[i] * speedDirection);
	}
	for (int i = 0; i < 6; i++)
	{
		m_backgroudX2[i] = m_backgroudX2[i] + (int)(m_speed[i] * speedDirection);
	}


	for (int& obj : m_backgroudX1)
	{
		if (obj < (-Config::SCREEN_WIDTH))
		{
			obj = Config::SCREEN_WIDTH;
		}

		if (obj > Config::SCREEN_WIDTH)
		{
			obj = (-Config::SCREEN_WIDTH);
		}
	}
	for (int& obj : m_backgroudX2)
	{
		if (obj < (-Config::SCREEN_WIDTH))
		{
			obj = Config::SCREEN_WIDTH;
		}

		if (obj > Config::SCREEN_WIDTH)
		{
			obj = (-Config::SCREEN_WIDTH);
		}
	}

	for (int i =0; i < 6; i++)
	{
		if (abs(m_backgroudX1[i]) + abs(m_backgroudX2[i]) != Config::SCREEN_WIDTH)
		{
			if (m_backgroudX1[i] - m_backgroudX2[i] > 0)
			{
				m_backgroudX2[i] = m_backgroudX1[i] - Config::SCREEN_WIDTH;
			}
			else if (m_backgroudX1[i] - m_backgroudX2[i] < 0)
			{
				m_backgroudX1[i] = m_backgroudX2[i] - Config::SCREEN_WIDTH;
			}
		}
	}

	//std::cout << m_backgroudX5 << std::endl;
	//std::cout << m_backgroudX55 << std::endl;
	m_prevCameraX = Camera::Instance().getPosition().x;
}

void Background::clean()
{
}
