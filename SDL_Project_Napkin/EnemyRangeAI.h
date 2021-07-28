#pragma once
#ifndef __ENEMY_RANGE_AI__
#define __ENEMY_RANGE_AI__
#include <glm/vec2.hpp>

#include "GameAI.h"

class Character;
class EnemyRangeAI : public GameAI
{
public:
	EnemyRangeAI(Character* character);
	~EnemyRangeAI() = default;
	void update() override;

private:

	glm::vec2 m_previousPostion;
};

#endif // __ENEMY_RANGE_AI__