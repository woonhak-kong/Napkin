#include "EnemyRangeAI.h"
#include <iostream>

#include "Character.h"
#include "Scene.h"
#include "SoundID.h"
#include "SoundManager.h"

EnemyRangeAI::EnemyRangeAI(Character* character) :
	GameAI(character),
	m_previousPostion({ 0,0 })
{
}

void EnemyRangeAI::update()
{

	glm::vec2 playerPosition = m_self->getParent()->getPlayer()->getCenterPosition();
	glm::vec2 selfPosition = m_self->getCenterPosition();

	int distanceX = abs(playerPosition.x - selfPosition.x);
	int distanceY = abs(playerPosition.y - selfPosition.y);
	float distance = sqrt(distanceX * distanceX + distanceY * distanceY);


	int direction;
	//std::cout << "distance : " << distance << std::endl;

	if (m_self->getParent()->getState() == SceneState::PLAY_SCENE2)
	{
		if (distance > 500)
		{
			m_self->idle();
		}
		else
		{
			direction = playerPosition.x - selfPosition.x;
			if (direction < 0)
			{
				m_self->setIsFlip(true);
			}
			else if (direction > 0)
			{
				m_self->setIsFlip(false);
			}
			m_self->attack();
		}
	}
	else if (playerPosition.y > selfPosition.y - 100 && playerPosition.y < selfPosition.y + 100)
	{


		if (distance > 500)
		{
			m_self->idle();
		}
		else
		{
			// if minus, player is on left side
			direction = playerPosition.x - selfPosition.x;
			if ((static_cast<float>(m_self->getPresentHp()) / static_cast<float>(m_self->getMaxHp())) > 0.2f)
			{
				if (distance > 300)
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
					m_self->attack();

				}
			}
			else
			{
				if (distance < 400)
				{

					/*if (m_previousPostion.x == selfPosition.x && m_self->getCurrentState() == CharacterState::RUN)
					{
						m_self->jump();
					}*/
					if (direction < 0)
					{
						m_self->moveToRight();
					}
					else if (direction > 0)
					{
						m_self->moveToLeft();
					}
					m_previousPostion = selfPosition;
				}

			}
		}
	}
	else
	{
		m_self->idle();
	}


}
