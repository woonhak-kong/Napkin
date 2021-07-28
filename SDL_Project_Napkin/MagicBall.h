#pragma once
#include "AttackBox.h"
#include "MagicBallType.h"

class MagicBall : public AttackBox
{
public:
	MagicBall(glm::vec2 point, glm::vec2 velocity, GameObjectType attackType, int power, MagicBallType type,  GameObject* target);
	~MagicBall() override;
	void draw() override;
	void update() override;
	void clean() override;
	void collision(DisplayObject* obj) override;


private:
	MagicBallType m_type;
	GameObject* m_pTarget;
	glm::vec2 m_pTargetPositionAtStart;
};

