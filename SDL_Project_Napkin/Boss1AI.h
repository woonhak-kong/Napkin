#pragma once
#ifndef __BOSS1_AI__
#define __BOSS1_AI__

#include "GameAI.h"
#include <glm/vec2.hpp>

class Character;
class Boss1AI : public GameAI
{
public:
	Boss1AI(Character* character);
	~Boss1AI();
	void update() override;

private:

	glm::vec2 m_previousPostion;
	float m_attackDelay;
};

#endif // __BOSS1_AI__