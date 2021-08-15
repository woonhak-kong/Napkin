#include "Boss1AI.h"

#include "Character.h"
#include "Game.h"
#include "Scene.h"

Boss1AI::Boss1AI(Character* character) :
	GameAI(character),
	m_previousPostion({ 0,0 }),
	m_attackDelay(2000)
{
}

Boss1AI::~Boss1AI()
{
}

void Boss1AI::update()
{

	glm::vec2 playerPosition = m_self->getParent()->getPlayer()->getCenterPosition();
	glm::vec2 selfPosition = m_self->getCenterPosition();

	int distanceX = abs(playerPosition.x - selfPosition.x);
	int distanceY = abs(playerPosition.y - selfPosition.y);
	float distance = sqrt(distanceX * distanceX + distanceY * distanceY);


	int direction;
	//std::cout << "distance : " << distance << std::endl;
	m_attackDelay += Game::Instance().getDeltaTime();
	//std::cout << m_attackDelay << std::endl;
	if (playerPosition.y > selfPosition.y - 100 && playerPosition.y < selfPosition.y + 100)
	{


		if (distance > 600)
		{
			m_self->idle();
		}
		else
		{
			// if minus, player is on left side
			direction = playerPosition.x - selfPosition.x;

			if (distance > 500)
			{

				if (m_previousPostion.x == selfPosition.x && m_self->getCurrentState() == CharacterState::RUN)
				{
					m_self->jump();
				}
				if (direction < 0)
				{
					m_self->moveToLeft();
				}
				else if (direction > 0)
				{
					m_self->moveToRight();
				}
				m_previousPostion = selfPosition;
			}
			else
			{
				if (direction < 0)
				{
					m_self->setIsFlip(true);
				}
				else if (direction > 0)
				{
					m_self->setIsFlip(false);
				}

				if (m_attackDelay > 3)
				{

					//std::cout << "==========================" << std::endl;
					m_self->attack();
					m_attackDelay = 0;

				}
				else
				{
					m_self->idle();
				}

			}

		}
	}
	else
	{
		m_self->idle();
	}

}
