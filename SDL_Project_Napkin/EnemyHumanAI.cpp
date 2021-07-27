#include "EnemyHumanAI.h"
#include <iostream>

#include "Character.h"
#include "Scene.h"
#include "SoundID.h"
#include "SoundManager.h"

EnemyHumanAI::EnemyHumanAI(Character* character) :
	GameAI(character),
	m_previousPostion({ 0,0 })
{
}

void EnemyHumanAI::update()
{

	glm::vec2 playerPosition = m_self->getParent()->getPlayer()->getCenterPosition();
	glm::vec2 selfPosition = m_self->getCenterPosition();

	int distanceX = abs(playerPosition.x - selfPosition.x);
	int distanceY = abs(playerPosition.y - selfPosition.y);
	float distance = sqrt(distanceX * distanceX + distanceY * distanceY);
	int direction = 0;
	//std::cout << "distance : " << distance << std::endl;

	if (playerPosition.y > selfPosition.y - 100 && playerPosition.y < selfPosition.y + 100)
	{


		if (distance > 500)
		{
			m_self->idle();
		}
		else
		{
			direction = playerPosition.x - selfPosition.x;
			if ((static_cast<float>(m_self->getPresentHp()) / static_cast<float>(m_self->getMaxHp())) > 0.2f )
			{
				if (distance > 50)
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

					m_self->attack();

				}
			}
			else
			{
				if (distance < 100)
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
