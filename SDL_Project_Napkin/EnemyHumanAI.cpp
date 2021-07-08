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

	int distance = abs(playerPosition.x - selfPosition.x);
	int direction = 0;
	//std::cout << "distance : " << distance << std::endl;
	if (distance > 500)
	{
		m_self->idle();
	}
	else
	{
		direction = playerPosition.x - selfPosition.x;
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

}
